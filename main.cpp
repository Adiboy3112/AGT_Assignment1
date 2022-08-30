#include <bits/stdc++.h>

using namespace std;
extern "C"
{
        struct parsedInfo {
                int rows;
                int cols;
                int **arr;
        };
        struct parsedInfo *parser(char *filename);
        int yyparse(void);
        int yylex(void);  
        int yywrap()
        {
                return 1;
        }
}


int rows1=27;
int columns=3;
int nstrategy=3;

vector<vector<int>> wds(columns);
vector<vector<int>> vwds(columns);
vector<vector<int>> comb;


void FindNE(int player, int **u,vector<int> s,int **strategy, int *ne)
{
    int shift=1;
    vector<int> visited(rows1,0);
    for(int i=0;i<player;i++)
    {
        shift *=s[i];
    }
    int i=0;
    multiset<int> set1;
    int x=0;
   
    while(i<rows1)
    {
        
        if(visited[i]==1)
        {
            i++;
            continue;
        }
        x++;
        int index=0;
        int maxi=u[i][player];
        visited[i]=1;
        int a=0;
        strategy[i][player]=a;
    
        for(int j=i+shift;j<i+(shift)*(s[player]);j+=shift)
        {
            a++;
            strategy[j][player]=a;
            if(u[j][player]>=maxi)
            {
                
                ne[j]+=1; 
                
            }
            else{
                ne[j]=-1;
            }



            visited[j]=1;

        }

        i++;
    }

}



void combinations(vector<vector<int> > array, int i, vector<int> accum)
{
    if (i == array.size()) // done, no more rows1
    {
        comb.push_back(accum); // assuming comb is global
    }
    else
    {
        vector<int> row = array[i];
        for(int j = 0; j < row.size(); ++j)
        {
            vector<int> tmp(accum);
            tmp.push_back(row[j]);
            combinations(array,i+1,tmp);
        }
    }
}

void displaystrategies()
{
    for (int i = 0; i < comb.size(); i++)
    {
        for (int j = 0; j < comb[i].size(); j++)
        {
            cout<<comb[i][j]+1<<" ";
        }
        comb[i].clear();
        cout<<endl;
    }
    comb.clear();
    
}

int SDS(int player, int **u,vector<int> s)
{
    int shift=1;
    vector<int> visited(rows1,0),v;
    for(int i=0;i<player;i++)
    {
        shift *=s[i];
    }
    int i=0;
    while(i<rows1)
    {
        int flag=1;
        if(visited[i]==1)
        {
            i++;
            continue;
        }
        int index=0;
        int maxi=u[i][player];
        visited[i]=1;
        int a=0;
        for(int j=i+shift;j<i+(shift)*(s[player]);j+=shift)
        {
            a++;
            if(u[j][player]>maxi)
            {
                maxi=u[j][player];
                flag=1;
                index=a;
            
            }
            else if(u[j][player]==maxi)
            {
                flag=0;
                
            }
            visited[j]=1;
        }
        if(flag)
        {
            v.push_back(index);
        
        }  
        else return -1;
        i++;
    }
    int prev=v[0];
    for(int i=0;i<v.size();i++)
    {
        if(v[i]!=prev)
        {
            return -1;
        }
    }
    return prev;
}
void WDS(int player, int **u,vector<int> s)
{
    int shift=1;
    vector<int> visited(rows1,0),v(s[player],0);
    for(int i=0;i<player;i++)
    {
        shift *=s[i];
    }
    int i=0;
    multiset<int> set1;
    int x=0;
    while(i<rows1)
    {
        
        if(visited[i]==1)
        {
            i++;
            continue;
        }
        x++;
        int index=0;
        int maxi=u[i][player];
        visited[i]=1;
        int a=0;
        set1.insert(index);
        for(int j=i+shift;j<i+(shift)*(s[player]);j+=shift)
        {
            a++;
            if(u[j][player]>maxi)
            {
                maxi=u[j][player];
                
                set1.erase(set1.find(index));
                index=a;
                set1.insert(index);
            
            }
            else if(u[j][player]==maxi)
            {
             
                index=a;
                set1.insert(index);
                
            }
            else
            {   
                v[index]=1;
                
            }
            visited[j]=1;
        }

        i++;
    }
 
       for(int i=0;i<s[player];i++)
       {
            if(set1.count(i)==x&&v[i]==1)
            {
                wds[player].push_back(i);
               
            }
        
       }
   
}
void VWDS(int player, int **u,vector<int> s)
{
    int shift=1;
    vector<int> visited(rows1,0);
    for(int i=0;i<player;i++)
    {
        shift *=s[i];
    }
    int i=0;
    multiset<int> set1;
    int x=0;
    while(i<rows1)
    {
        
        if(visited[i]==1)
        {
            i++;
            continue;
        }
        x++;
        int index=0;
        int maxi=u[i][player];
        visited[i]=1;
        int a=0;
        set1.insert(index);
        for(int j=i+shift;j<i+(shift)*(s[player]);j+=shift)
        {
            a++;
            if(u[j][player]>maxi)
            {
                maxi=u[j][player];
                
                set1.erase(set1.find(index));
                index=a;
                set1.insert(index);
            
            }
            else if(u[j][player]==maxi)
            {
             
                index=a;
                set1.insert(index);
                
            }


            visited[j]=1;
        }

        i++;
    }
 
       for(int i=0;i<s[player];i++)
       {
            if(set1.count(i)==x)
            {
                vwds[player].push_back(i);
               
            }
        
       }
   
}





int main(int argc, char *argv[])
{
    cout<<endl;
    struct parsedInfo *pi = parser(argv[1]);
    rows1=pi->rows;
    columns=pi->cols;
    int **u = pi->arr;
    vector<int>s(columns);


    for (int i = 0; i < columns; i++)
    {
        cout<<"Enter no of strategies for player "<<i+1<<" :";
        cin>>s[i];
    }
    cout<<endl;
    cout<<endl;
    
    int sds[columns];
    



    for (int i = 0; i < columns; i++)
    {
        sds[i]=SDS(i,u,s);
        WDS(i,u,s);
        VWDS(i,u,s);
    
    }
    cout<<"Q1 Does Dominant Strategies exist?"<<endl<<endl;
    // display dominant strategies
    for (int i = 0; i < columns; i++)
    {
        if(sds[i]==-1)cout<<"Dominant Strategies for player "<<i+1<<" don't exist"<<endl;
        else cout<<"Dominant Strategies for player "<<i+1<<" is "<<sds[i]+1<<endl;
    }
    cout<<endl;

    // display weakly dominant strategies
    cout<<"Q2 Does Weakly Dominant Strategies exist?"<<endl<<endl;

    for (int i = 0; i < columns; i++)
    {
        if(wds[i].empty())cout<<"Weakly Dominant Strategies for player "<<i+1<<" don't exist"<<endl;
        else 
        {
            cout<<"Weakly Dominant Strategies for player "<<i+1<<" is: ";
            for (int j = 0; j < wds[i].size(); j++)
            {
                cout<<wds[i][j]+1<<" ";
            }
            cout<<endl;
            
        }
    

    }
    cout<<endl;
    // display very weakly dominant strategies
    cout<<"Q3 Does Very Weakly Dominant Strategies exist?"<<endl<<endl;

    for (int i = 0; i < columns; i++)
    {
        if(vwds[i].empty())cout<<"Very Weakly Dominant Strategies for player "<<i+1<<" don't exist"<<endl;
        else 
        {
            cout<<"Very Weakly Dominant Strategies for player "<<i+1<<" is: ";
            for (int j = 0; j < vwds[i].size(); j++)
            {
                cout<<vwds[i][j]+1<<" ";
            }
            cout<<endl;
            
        }

    }
    cout<<endl;

    // check for SDSE
    cout<<"Q4 Does SDS Equilibrium exist?"<<endl<<endl;
    bool SDSE=true;
    vector<int>sdse;
    for (int i = 0; i < columns; i++)
    {
        if(sds[i]==-1)
        {
            SDSE=false;
            break;

        }
        else sdse.push_back(sds[i]);

    }
    if(SDSE)
    {
        cout<<"The SDSE for this game exists for the strategy: ";
        for (int i = 0; i < columns; i++)
        {
           cout<<sdse[i]+1<<" ";

        }
        cout<<endl;
        
    }
    
    else
    {
        cout<<"The SDSE for this game dosen't exist"<<endl;
    }
    cout<<endl;
    // check for WDSE
    cout<<"Q5 Does WDS Equilibrium exist?"<<endl<<endl;
    bool WDSE=true;

    for(int i = 0; i < columns; i++)
    {
    /* code */
        if(wds[i].empty())
        {
            WDSE=false;
            break;
        }   
    }
    if(WDSE)
    {
        cout<<"The WDSE for this game exists for the strategy: \n";
        vector<int> acum;
        combinations(wds,0,acum);
        displaystrategies();
    }
    else 
    {
        cout<<"The WDSE for this game dosen't exist"<<endl;
    }
    cout<<endl;
    // check for VWDSE
    
    cout<<"Q6 Does VWDS Equilibrium exist?"<<endl<<endl;
    bool VWDSE=true;

    for(int i = 0; i < columns; i++)
    {
    /* code */
        if(vwds[i].empty())
        {
            VWDSE=false;
            break;
        }   
    }
    if(VWDSE)
    {
        cout<<"The VWDSE for this game exists for the strategy: \n";
        vector<int> acum;
        combinations(vwds,0,acum);
        displaystrategies();
    }
    else
    {
        cout<<"The VWDSE for this game dosen't exist"<<endl;
    }
    cout<<endl;
    int **strategy;
    strategy = new int*[rows1];
    int ne[rows1];

    for (int i = 0; i < rows1; i++)
    {
        strategy[i]= new int[columns];
        ne[i]=0;
    }
  

    for (int i = 0; i < columns; i++)
    {
        FindNE(i,u,s,strategy,ne);

    }

    
    
    
}
