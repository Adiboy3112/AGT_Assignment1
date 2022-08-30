#include <bits/stdc++.h>

using namespace std;
int rows=4;
int columns=2;
vector<int> ans;

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
                ans.push_back(i);
               
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
                ans.push_back(i);
               
            }
        
       }
   
}



int main()
{

    int u[8][2];
    vector<int>s(2);
    s[0]=2;
    s[1]=2;
    u[0][0]=3;
    u[0][1]=1;
    u[1][0]=2;
    u[1][1]=2;
    u[2][0]=0;
    u[2][1]=0;
    u[3][0]=2;
    u[3][1]=2;
    WDS(0,u,s);
    cout<<ans.size()<<endl;
}
