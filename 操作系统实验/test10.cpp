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


void allocate();void recycle();void display();

struct AllocatedSpace
{
	int start_address;
	int length;
	char job;
	struct AllocatedSpace *next;
	
	AllocatedSpace(){}
	AllocatedSpace(int start_address,int length,char job){
		this->start_address=start_address;
		this->length=length;
		this->job=job;
		this->next=NULL;
	}
};

struct FreeSpace{
	int start_address;
	int length;
	struct FreeSpace *next;
	FreeSpace(){}
	FreeSpace(int start_address,int length){
		this->start_address=start_address;
		this->length=length;
		this->next=NULL;
	}
};



FreeSpace* free_head; 
AllocatedSpace* allocated_head;

void init()
{
	free_head=new FreeSpace();
	allocated_head=new AllocatedSpace();
	FreeSpace *tmp=new FreeSpace();
	
	tmp->length=100000;
	tmp->start_address=0;
	tmp->next=NULL;
	free_head->next=tmp;
	
	allocated_head->next=NULL; 
}


void table()
{
	cout<<"0:退出"<<endl<<"1:分配"<<endl<<"2:回收"<<endl<<"3:显示"<<endl; 
	int choice;
	cin>>choice;
	switch(choice)
	{
		case 0:
			exit(1);
			recycle();
			break;
		case 1:
			allocate();
			break;
		case 2:
			recycle();
			break;
		case 3:
			display();
			break;
		default:
			break;
	}
	
	
 } 
 
 
 void allocate()
 {
 	char job;
	 int require_length;
 	cout<<"输入作业名："<<endl;
 	cin>>job;
 	cout<<"输入要求内存大小："<<endl;
 	cin>>require_length;
 	
 	FreeSpace *tmp=free_head->next;
 	FreeSpace *pretmp=NULL; 
 	bool flag=0;
 	while(tmp!=NULL)
 	{
 		if(tmp->length>=require_length)
 		{
 			flag=1;
 			AllocatedSpace* allocated_tmp=allocated_head;
 			while(allocated_tmp->next!=NULL)
				allocated_tmp=allocated_tmp->next;
			AllocatedSpace* newallocated=new AllocatedSpace(tmp->start_address,require_length,job);
			allocated_tmp->next=newallocated;
			
			tmp->length=tmp->length-require_length;
			tmp->start_address+=require_length;
			break;
		 }
		 else
		 {
		 	pretmp=tmp;
		 	tmp=tmp->next;
		 }	
	 }
	 if(!flag) {cout<<"内存不足，无法分配"<<endl;};
}  
 
 
void integrate()
{
	FreeSpace* tmp1=free_head->next; 
	if(tmp1==NULL||tmp1->next==NULL)
		return ;
	while(tmp1!=NULL&&tmp1->next!=NULL)
	{
		cout<<"breakpoint  1"<<endl;
		FreeSpace* tmp2=tmp1->next;
		FreeSpace* pretmp2=tmp1;
		cout<<"breakpoint  2"<<endl;
		while(tmp2!=NULL)
		{
		cout<<"breakpoint  3"<<endl;
			if((tmp1->start_address+tmp1->length)==tmp2->start_address)	
				{
					tmp1->length+=tmp2->length;
					pretmp2->next=tmp2->next;
				}				
			pretmp2=tmp2;
			tmp2=tmp2->next; 			
		}	
		tmp1=tmp1->next;
	}	
}

void SORT()
{
	if(free_head->next==NULL||free_head->next->next==NULL)
		return;
	FreeSpace* tmp1=free_head->next; 
		while(tmp1!=NULL)
		{
			FreeSpace* tmp2=tmp1->next;
			while(tmp2!=NULL)
			{
				if(tmp1->length>tmp2->length)
				{
					int addtmp=tmp1->start_address;
					int lentmp=tmp1->length;
					tmp1->length=tmp2->length;
					tmp1->start_address=tmp2->start_address;
					tmp2->length=lentmp;
					tmp2->start_address=addtmp; 
				}
				tmp2=tmp2->next;
			}
			tmp1=tmp1->next; 
		}
}

 
 void recycle()
{
 	char job;
 	cout<<"输入作业名："<<endl;
 	cin>>job;
 	AllocatedSpace* tmp1=allocated_head;
 	
 	while(tmp1->next!=NULL&&tmp1->next->job!=job)
 		tmp1=tmp1->next;
 		
	FreeSpace* tmp2=free_head;
	while(tmp2->next!=NULL)
		tmp2=tmp2->next;
		
	if(tmp1->next->job==job)
	{
		tmp2->next=new FreeSpace(tmp1->next->start_address,tmp1->next->length) ;
 		AllocatedSpace* trash=tmp1->next;
 		if(tmp1->next->next!=NULL)
 		tmp1->next=tmp1->next->next;
 		else
 		tmp1->next=NULL;
 		delete(trash);
 		integrate();	
 		SORT();
	}
	else
	{
		cout<<"不存在这个任务"<<endl; 
	}
} 

void display()
{
	AllocatedSpace* tmp1=allocated_head->next;
	FreeSpace* tmp2=free_head->next; 
	cout<<"*****内存分配情况******"<<endl; 
	while(tmp1!=NULL)
	{
		cout<<"作业名："<<tmp1->job<<"起始地址："<<tmp1->start_address<<"长度：" <<tmp1->length<<endl;
		tmp1=tmp1->next; 
	}
	cout<<"************************"<<endl;
	cout<<"*****空闲区情况******"<<endl; 
	while(tmp2!=NULL)
	{
		cout<<"起始地址："<<tmp2->start_address<<"长度：" <<tmp2->length<<endl;
		tmp2=tmp2->next; 
	}
	cout<<"************************"<<endl;
}

int main()
{
	init();
	while(1)
		table();	
	return 0;
 }

