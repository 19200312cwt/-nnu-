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
//��������ͳ�Ƹ��ʵ�	
if(temp>50)
	max++; 

printf("%d\n", temp);

}

//����ĸ��ʴ����50%����
printf("%f\n", (float)max/3000);

}


