#include<stdio.h>
#include<pthread.h>
#include<ctype.h>
#include<semaphore.h>
#include<stdlib.h>

sem_t mutex;
int total_words=0;
void *count_words(void *);
int main(int ac,char *av[])
{	
	if(ac!=3)
	{
		printf("Usage:%s file1 file2\n",av[0]);
		exit(1); 
	}
	sem_init(&mutex,0,1);
	count_words(av[1]);
	count_words(av[2]);
	printf("%d\n",total_words);
	sem_destroy(&mutex);
	return 0;
 }

void *count_words(void *arg)
{
	char *filename=(char*)arg;
	FILE *fp;
	int c,prevc='\0';
	if((fp=fopen(filename,"r"))!=NULL)
	{
		while((c=getc(fp))!=EOF)
		{
			if(!isalnum(c)&&isalnum(prevc))
			{
				
				sem_wait(&mutex);
				total_words++;
				sem_post(&mutex);
			}
			prevc=c;
		}
		fclose(fp);
	}
	else
		perror(filename);
		return NULL;
}

