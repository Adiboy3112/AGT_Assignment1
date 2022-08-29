#include <bits/stdc++.h>

using namespace std;
int rows=4;
int columns=2;

int SDS(int player, int u[8][2],vector<int> s)
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
int main()
{

    int u[8][2];
    vector<int>s(2);
    s[0]=2;
    s[1]=2;
    u[0][0]=3;
    u[0][1]=1;
    u[1][0]=1;
    u[1][1]=2;
    u[2][0]=2;
    u[2][1]=3;
    u[3][0]=1;
    u[3][1]=4;
    int a=SDS(1,u,s);
    cout<<a<<endl;
}
