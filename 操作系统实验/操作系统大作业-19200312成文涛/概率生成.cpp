#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

int main( )
{
int i;
int max,temp;
srand((unsigned)time( NULL ) );  
for(i = 0; i < 3000;i++){
	temp=rand()%100+1;
//这是用来统计概率的	
if(temp>50)
	max++; 

printf("%d\n", temp);

}

//输出的概率大概是50%上下
printf("%f\n", (float)max/3000);

}


