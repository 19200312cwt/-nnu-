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
#include<time.h>
#include<windows.h>
#define ll long long
using namespace std;



//�ڴ�   ҳ���С 1<<8 �ֽ�    ҳ����: 1<<6 ��  0��ҳ��Ϊҳ�� 
unsigned char *mem=(unsigned char*)malloc(1<<14); 
//λͼ
bool  bitmap[1<<6]={0};
queue<int> Q_FIFO;
queue<int> Q_LRU;
//ҳ������� 
int   empty=1<<6;

int addr[543516];


//Ϊ���̷���ҳ�� 
void pagealloc(int process_id)
{
	if(empty<10) 
	{
		printf("����ҳ��С��10������ʧ��");
		return; 
	}
	int cnt=0;
	for(int i=0;i<(1<<6);i++)
	{
		if(cnt==10)
			return;
		if(bitmap[i]==0)
		{
			//�ҿ���ҳ�� �� i*256 �ֽڴ�д����ҵ�� ҳ��� 
			//ֻд��  ��ҵ��
			//��i������ҳ���ַΪ��  256*i ---- 256*i+255 
			cnt++;
			mem[256*i] =process_id;
			bitmap[i]=1;
			empty--;
		}
	}
 } 
 
 /*��ҳ�����������޸�λͼ*/ 
 //��δʵ��ʵ���Ե�ҳ�����ݵ��޸Ĳ��� 
 int add(int logic_addr,int replaced)
 {
 	int mem_logic_addr=0;
 	int frame=0;
 	if(replaced==0)
 	{
 		for(int i=1;i<64;i++)
		{
		 	if(bitmap[i]==0)
		 	{
		 		bitmap[i]==1;	
		 		empty--;
				/*��ҳ������д��Ϣ*/
				for(int j=0;j<64;j++)
				{
					frame=(mem[j*4+2]<<8)+mem[j*4+3];
					if(frame!=0)
					{
						mem[j*4+0]=(logic_addr>>8);
						mem[j*4+1]=(logic_addr);
						mem[j*4+2]=(i>>8);
						mem[j*4+3]=i;
					}
				}	
		 		return i;	
			 }
		  }	
	 }
	 else
	 {
	 	for(int j=0;j<64;j++)
			{
				mem_logic_addr=(mem[j*4+0]<<8)+mem[j*4+1];
				if(mem_logic_addr==replaced)
				{
					mem[j*4+0]=(logic_addr>>8);
					mem[j*4+1]=(logic_addr);
				}
	 		 }
 	
 }}
 /*���ش�������ҳ���*/
 int FIFO(int logic_addr)
 {
 	if(empty>0)
		{
		 	Q_FIFO.push(logic_addr);
		 	return (add(logic_addr,0));
		} 
		else
		{
			int replaced=Q_FIFO.front();
			Q_FIFO.pop();
			Q_FIFO.push(logic_addr);
			return (add(logic_addr,replaced));
		}
 	return -1;
	
 }
 
 int LRU(int logic_addr)
 {
 	if(empty>0)
		{
		 	Q_LRU.push(logic_addr);
		 	return (add(logic_addr,0));
		} 
		else
		{
			int replaced=Q_FIFO.front();
			Q_LRU.pop();
			Q_LRU.push(logic_addr);
			return (add(logic_addr,replaced));
		}
 	return -1;
 }
 
 /*
 	��ҳ��
	1.���ڴ�:
		�����߼���ַ����ҳ���ַ 
	2.�����ڴ棺 
		1.û�� �Ҹ��յ�ҳ�棬����ҳ���ַ 
		2.���ˣ������滻�㷨�滻������ҳ���ַ 
*/
int pagevisit(int process_id,int logic_addr)
{
	int mem_logic_addr;
	bool flag=false;
	for(int i=0;i<64;i++)
	{
		//mem[i*4] mem[i*4+1]     mem[i*4+2] mem[i*4+3]
		mem_logic_addr=(mem[i*4]<<8)+mem[i*4+1];
		if(mem_logic_addr==logic_addr)
		{
			cout<<"mem_logic_addr: "<<mem_logic_addr<<endl;
			flag=true;
			/*������ �޸�LRU��λͼ*/
			Q_LRU.push(logic_addr);
			queue<int> tmp;
			while(!Q_LRU.empty())
			{
				if(Q_LRU.front()==logic_addr)
					continue;
				tmp.push(Q_LRU.front());
				Q_LRU.pop();
			}
			Q_LRU=tmp;
			Q_LRU.push(logic_addr);
						
			return int(mem[i*4+2]<<8+mem[i*4+3]);
		}
//		cout<<mem[i*4]<<"   "<<mem[i*4+1];
		printf("%d  %d",mem[i*4],mem[i*4+1]);
		cout<<"��"<<i<<"���߼���ַ��"<<mem_logic_addr<<endl;
	 } 
	 	int choice; 
	 	cout<<"�滻�㷨ѡ��1.	FIFO  2.LRU";
		cin>>choice;
		switch(choice)
		{
			case 1:
				return FIFO(logic_addr);
				break;
			case 2:
				return LRU(logic_addr);
				break;
		}
}
void addr_init()
{
	int pos=0;
	int area=0;
	for(int i=1;i<=(1<<16);i++)
	{
		area=ceil(1000/sqrt(i+1));
		while(area--)
		{
			addr[pos++]=i;
		}
	}
//	cout<<"pos:" <<pos<<endl;
}

int addr_visit(int rand)
{	
	return addr[rand%543517];
} 

int main()
{
	
//	printf("%d\n",mem[0]);
//	cout<<mem[0]<<endl;
	addr_init() ;
	//ҳ��ռ�õ�0��ҳ�� 
	memset(mem,0,sizeof(unsigned char)*(1<<14)); 
	empty--; bitmap[0]=1;
	srand((unsigned)time(NULL)); 
	
//	for(int i=0;i<200;i++)
//		printf("%d ,",page_visit(rand()));
	pagevisit(1,1);
	
	return 0;
 }

