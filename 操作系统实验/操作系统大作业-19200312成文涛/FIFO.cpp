#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#include<stack>
#include<queue>
#include<ctime>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;

#define N 10

int main()
{
    int ym[]={4,3,2,1,4,3,5,4,3,2,1,5};
	int sum=12;
    int allchangetimes=0;
    int fifo[N]={0};
    int n;
    int dq=0;

    cout<<"ÊäÈëÒ³¿ò´óÐ¡£º";
    cin>>n;
    for(int i=n-1;i>=0;i--)
    {
        fifo[i]=ym[dq++];
    }

            for(int i=0;i<n ;i++)
        {
            cout<<fifo[i]<<"   ";
        }
        cout<<endl;


    for(int j=n;j<sum;j++)
    {    int flag=0;
        for(int i=0;i<n;i++)
        {
            if(fifo[i]==ym[j])
            {  flag=1;

                break;
            }
        }

        if(flag==0)
        {
            allchangetimes++;
            for(int i=n-1;i>=1;i--)
            {
                fifo[i]=fifo[i-1];
            }
                fifo[0]=ym[j];
        }


        for(int i=0;i<n;i++)
        {
            cout<<fifo[i]<<"   ";
        }
        cout<<endl;
    }

    cout<<"È±Ò³"<<allchangetimes+n<<"´Î£¬"<<"ÖÃ»»"<<allchangetimes<<endl;
}
