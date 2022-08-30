#include <bits/stdc++.h>

using namespace std;
int rows=4;
int columns=2;

vector<vector<int>> wds(columns);
vector<vector<int>> vwds(columns);
vector<vector<int>> comb;

void combinations(vector<vector<int> > array, int i, vector<int> accum)
{
    if (i == array.size()) // done, no more rows
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
            cout<<comb[i][j]<<" ";
        }
        comb[i].clear();
        cout<<endl;
    }
    comb.clear();
    
}

int SDS(int player, int u[4][2],vector<int> s)
{
    int shift=1;
    vector<int> visited(rows,0),v;
    for(int i=0;i<player;i++)
    {
        shift *=s[i];
    }
    int i=0;
    while(i<rows)
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
void WDS(int player, int u[4][2],vector<int> s)
{
    int shift=1;
    vector<int> visited(rows,0),v(s[player],0);
    for(int i=0;i<player;i++)
    {
        shift *=s[i];
    }
    int i=0;
    multiset<int> set1;
    int x=0;
    while(i<rows)
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
void VWDS(int player, int u[4][2],vector<int> s)
{
    int shift=1;
    vector<int> visited(rows,0);
    for(int i=0;i<player;i++)
    {
        shift *=s[i];
    }
    int i=0;
    multiset<int> set1;
    int x=0;
    while(i<rows)
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





int main()
{

    int u[8][2],sds[columns];
    vector<int>s(columns);
    s[0]=2;
    s[1]=2;
    u[0][0]=3;
    u[0][1]=1;
    u[1][0]=1;
    u[1][1]=2;
    u[2][0]=4;
    u[2][1]=1;
    u[3][0]=2;
    u[3][1]=2;
    for (int i = 0; i < columns; i++)
    {
        sds[i]=SDS(i,u,s);
        WDS(i,u,s);
        VWDS(i,u,s);
    
    }
    // check for SDSE
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
           cout<<sdse[i]<<" ";

        }
        cout<<endl;
        
    }
    
    else
    {
        cout<<"The SDSE for this game dosen't exist"<<endl;
    }

    // check for WDSE
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

    // check for VWDSE
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


    
}
