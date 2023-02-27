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



//内存   页面大小 1<<8 字节    页面数: 1<<6 个  0号页框为页表 
unsigned char *mem=(unsigned char*)malloc(1<<14); 
//位图
bool  bitmap[1<<6]={0};
queue<int> Q_FIFO;
queue<int> Q_LRU;
//页框计数器 
int   empty=1<<6;

int addr[543516];


//为进程分配页框 
void pagealloc(int process_id)
{
	if(empty<10) 
	{
		printf("空闲页面小于10，分配失败");
		return; 
	}
	int cnt=0;
	for(int i=0;i<(1<<6);i++)
	{
		if(cnt==10)
			return;
		if(bitmap[i]==0)
		{
			//找空闲页面 第 i*256 字节处写入作业号 页面号 
			//只写入  作业号
			//第i个物理页面地址为：  256*i ---- 256*i+255 
			cnt++;
			mem[256*i] =process_id;
			bitmap[i]=1;
			empty--;
		}
	}
 } 
 
 /*在页表里添加项，并修改位图*/ 
 //但未实现实质性的页框数据的修改操作 
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
				/*在页表中填写信息*/
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
 /*返回存入物理页框号*/
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
 	找页表
	1.在内存:
		根据逻辑地址返回页框地址 
	2.不在内存： 
		1.没满 找个空的页面，返回页框地址 
		2.满了，根据替换算法替换，返回页框地址 
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
			/*命中了 修改LRU的位图*/
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
		cout<<"第"<<i<<"项逻辑地址："<<mem_logic_addr<<endl;
	 } 
	 	int choice; 
	 	cout<<"替换算法选择：1.	FIFO  2.LRU";
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
	//页表占用第0号页框 
	memset(mem,0,sizeof(unsigned char)*(1<<14)); 
	empty--; bitmap[0]=1;
	srand((unsigned)time(NULL)); 
	
//	for(int i=0;i<200;i++)
//		printf("%d ,",page_visit(rand()));
	pagevisit(1,1);
	
	return 0;
 }

