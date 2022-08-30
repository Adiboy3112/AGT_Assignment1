/* WORKS FOR LINUX ONLY.
    FOR WINDOWS : Change "/dev/null" to "NUL"
                  Use appropriate C headers for strtok and other std library functions 
*/
%{
#include<stdio.h>
#include<string.h>

struct parsedInfo {
    int rows;
    int cols;
    int **arr;
};

void lexRow(char *yytext, int yyleng);
void lexInt(char *yytext, int yyleng);
int parseFile(char *file);
void parseInput(char *input, int *arr);
struct parsedInfo *parser(char *file);

int rows=0;
int cols=0;
char *numInputStr;

int **arr_temp;
%}

/*********** declaring expressions */

rowInput "{ \"\" "[0-9]+[, 0-9]+"}"
numInput ^[0-9+ ]+

/********** Rules Section*/
%%

{rowInput}  {lexRow(yytext,yyleng);}
{numInput} {lexInt(yytext,yyleng);}

%%

/********* Normal Code */

/* 
    This function takes row of the form { "" 1, 2, ....} and then extracts
    integers and adds them to a row 
*/
void lexRow(char *yytext, int yyleng){
    arr_temp = realloc(arr_temp,(rows+1)*sizeof(int *));
    char *token, *str;
    token = strtok(yytext,"\"");
    token = strtok(NULL,"\"");
    token = strtok(token,"}");

    str = token;

    cols = 0;
    for(int i=0 ; ;i++,str=NULL){
        token = strtok(str,", ");
        if(token == NULL)
            break;

        cols++;
        arr_temp[rows] = realloc(arr_temp[rows],(i+1)*sizeof(int));
        arr_temp[rows][i] = atoi(token);
    }

    rows++;
}

/* 
    This function takes row of the form 1 2 3 25 4 5 .... and then extracts 
    integers and adds them to the numInput array 
*/
void lexInt(char *yytext, int yyleng){
    numInputStr = malloc(sizeof(char)*yyleng);
    strncpy(numInputStr,yytext,yyleng-1);
}

/* 
    This function opens the file and calls lex on it
    on error -1 is returned else any any positive number 
*/
int parseFile(char *file){

    FILE *fp = fopen(file,"r");
    if(fp == NULL){
        return -1;
    }
    /* set input file as input to lex */
    yyin = fp;

    /* sending the miscellanous output of the file contents by
        yylex() to /dev/null.
    */
    yyout= fopen("/dev/null","w");

    yylex();

    fclose(fp);
    return 0;
}

void parseInput(char *input, int *arr){
    char *token, *str;
    str = input;

    for(int i=0; ;i++,str=NULL){
        token = strtok(str," ");
        if(token == NULL)
            break;

        arr[i] = atoi(token);
    }
}

struct parsedInfo *parser(char *file){
    struct parsedInfo *pi = malloc(sizeof(struct parsedInfo));
    int **arr;
    int ret;

    if((ret = parseFile(file)) == -1){
        fprintf(stderr,"Error in parseFile\n");
        return NULL;
    }

    int *numInput = malloc(sizeof(int)*rows);
    parseInput(numInputStr, numInput);

    /* rows will be defined here when execution comes */
    arr = malloc(rows * sizeof(int *));
    
    for(int i=0;i<rows;i++){
        arr[i] = arr_temp[numInput[i]-1];
    }

    printf("Rows : %d\n",rows);
    printf("Columns : %d\n",cols);

    for(int i=0 ;i<rows; i++){
        for(int j=0;j<cols;j++){
            printf("NUM[%d][%d] : %d\t",i,j,arr[i][j]);
        }
        printf("\n");
    }

    pi->rows = rows;
    pi->cols = cols;
    pi->arr = arr;

    return pi;
}
