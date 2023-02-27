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

int main()
{
	double ans=0;
	int cnt=0;
	for(int i=1;i<=(1<<16);i++)
	{
		ans+=(1/sqrt(i+1));
//		cout<<(1/sqrt(i+1))<<endl;
		cnt+=ceil(1000/sqrt(i+1));
	 } 
//	 cout<<(1/ans);
		cout<<"CNT:	"<<cnt<<endl;
	return 0;
 }

