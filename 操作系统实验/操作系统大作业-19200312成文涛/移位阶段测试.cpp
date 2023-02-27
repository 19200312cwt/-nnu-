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
	unsigned char a1=0;
	unsigned char a2=0;
	int b=0x00001234;
	a1=b;
	a2=(b>>8);
	printf("%0x  , %0x",a1,a2);
	return 0;
 }


