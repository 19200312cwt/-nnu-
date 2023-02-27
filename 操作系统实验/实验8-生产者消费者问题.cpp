#include<stdio.h>
#include<pthread.h>
#include<ctype.h>
#include<semaphore.h>
#include<stdlib.h>
#include<windows.h>
#include<unistd.h>
#include<Processthreadsapi.h>
#include<iostream>

int num=0;
const int k=10,m=3,n=2;


int in=0,out=0; 
int buffer[10];
sem_t cmutex,pmutex,empty,full,mutex;

pthread_t pro1,pro2,pro3;
pthread_t con1,con2;

void* producer(void *a);
void* consumer(void *b);


int main() {
	memset(buffer,0,sizeof(buffer));
	sem_init(&empty,0,k);
	sem_init(&full,0,0);
	sem_init(&pmutex,0,1);
	sem_init(&cmutex,0,1);
	sem_init(&mutex,0,1);
	pthread_create(&pro1, NULL, producer, &pro1); 
	pthread_create(&pro2, NULL, producer, &pro2);
	pthread_create(&pro3, NULL, producer, &pro3);
	pthread_create(&con1, NULL, consumer, &con1);
	pthread_create(&con2, NULL, consumer, &con2);
	pthread_join(pro1,NULL);
	pthread_join(pro2,NULL);
	pthread_join(pro3,NULL);
	pthread_join(con1,NULL);
	pthread_join(con2,NULL);
	sem_destroy(&pmutex);
	sem_destroy(&cmutex);
	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}

void buffer_display()
{
	int kucun=0;
	for(int i=0;i<k;i++)
	{
		if(buffer[i]>0)
			kucun++;
	}
	std::cout<<"库存："<<kucun<<std::endl;
 } 
void *producer(void *a) {
	while(1) {
		sem_wait(&empty);
		sem_wait(&mutex);
		num++;
		while(buffer[in]!=0)
			in=(in+1)%k;
		printf("tid=%d\t生产商品id=%d\t存入仓库：%d\n" ,GetCurrentThreadId(),num,in);
		buffer[in]=num;
		in=(in+1)%k;
		buffer_display();
		sem_post(&mutex);
		sem_post(&full);
		sleep(2);
	}
}

void *consumer(void *b) {
	while(1) {
		sem_wait(&full);
		sem_wait(&mutex);
		while(buffer[out]==0)
			out=(out+1)%k;
		buffer[out]=0;
		printf("tid=%d\t消费商品id=%d\t取出仓库：%d\n",GetCurrentThreadId(),num,out);
		buffer_display();
		out=(out+1)%k;
		sem_post(&mutex);
		sem_post(&empty);
		sleep(3);
	}
}
