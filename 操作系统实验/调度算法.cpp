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


int time_HRRF=100;

struct task {
	public:
		int id;
		int arrival;
		int cost=0;
		int priority=1;
	public:
		task(int _id,int _arrival,int _cost,int _priority):id(_id),arrival(_arrival),cost(_cost),priority(_priority) {}
		friend ostream &operator<<(ostream &out , const task &a) {
			out << "<task>( " << char(a.id+64) << ")"<<endl;
			return out;
		}
		bool operator < (const task &a) {
			return arrival<a.arrival;
		}
};
vector<task> tasks;
int Endtime[100];


struct cmp_FCFS {
	bool operator() (const task &a, const task &b) {
		if(a.arrival!=b.arrival)
			return a.arrival > b.arrival;  // '>' 是最小堆
		else
			return a.id>b.id;
	}
};

struct cmp_SJF {
	bool operator() ( const task &a, const task &b) {
			return a.cost>b.cost;
	}
};
struct cmp_HRRF{
	bool operator ()( const task &a, const task &b) {
			return (1+(time_HRRF -a.arrival)/a.cost)<(1+(time_HRRF -b.arrival)/b.cost);
	}
};
/*struct cmp_SJF_strive {
	bool operator() (const task &a, const task &b) {
		return a.cost>b.cost;
	}
};*/

/*queue<task> cmp_HRRF(vector<task> tasks) {
	//默认任务列表的到达系统的时间为降序
	queue<task> tasks_queue;
	tasks_queue.push(tasks[0]);
	tasks.erase(tasks.begin()+0);
	//for(auto it=tasks.begin();it!=tasks.end();it++)
	//		cout<<*it<<endl;
	int max_index=-1;
	int sum=tasks[0].cost;
	double max_rr=-1;
	while(!tasks.empty()) {
//		for(auto it=tasks.begin();it!=tasks.end();it++)
//			cout<<*it<<endl;
		max_rr=-1;
		for(int j=0; j<tasks.size(); j++) {
			double rr=1+ (sum-tasks[j].arrival)/tasks[j].cost;
			if(rr>max_rr) {
				max_rr=rr;
				max_index=j;
			}
		}
//		cout<<"min_index "<<min_index<<endl;
//		cout<<"tasks[min_index] "<<tasks[min_index]<<endl;
		tasks_queue.push(tasks[max_index]);
		sum+=tasks[max_index].cost;
		tasks.erase(tasks.begin()+max_index);
	}
	return tasks_queue;
}*/
/*bool cmp_FCFS(vector<task>&a,vector<task>&b){
	return a[0].arrival>a[0].arrival;
}*/
//priority_queue<task, vector<task>, cmp_FCFS> tasks_queue;
//priority_queue<task, vector<task>, cmp_FCFS> Q;

void init() {
	tasks.push_back(task(1,0,3,1));
	tasks.push_back(task(2,2,6,1));
	tasks.push_back(task(3,4,4,1));
	tasks.push_back(task(4,6,5,1));
	tasks.push_back(task(5,8,2,1));
}

void output()
{
	double T=0,W=0;	
	double tmp_T=0,tmp_W=0;
	for(int i=0;i<tasks.size();i++)
	{
		tmp_T=Endtime[tasks[i].id]-tasks[i].arrival;
		tmp_W=tmp_T/tasks[i].cost;
		T+=tmp_T; 
		W+=tmp_W;
	}
	T/=tasks.size();
	W/=tasks.size();
	cout<<"平均周转时间为："<<T<<endl<<"带权周转时间为："<<W<<endl; 
}
void FCFS() {
	int time =0;
	priority_queue<task,vector<task>,cmp_FCFS> tasks_queue;
	for(int i=0; i<tasks.size(); i++)
		tasks_queue.push(tasks[i]);
	priority_queue<task,vector<task>,cmp_FCFS> pq_copy {tasks_queue};
	while (!pq_copy. empty()) {
		cout << char(pq_copy.top().id+64)<<endl;
		cout<<"start: "<<time<<"  "<<"end: "<<time+pq_copy.top().cost<<endl;
		time+=pq_copy.top().cost;
		Endtime[pq_copy.top().id]=time;
		pq_copy.pop();
	}
	cout<<"FCFS:"<<endl;
	output();
}

void SJF()
{
	priority_queue<task,vector<task>,cmp_SJF> tasks_queue;
	task Event(-1,0,0,0);
	int time=0,i=0;
	while(1) {
		cout<<"T:"<<time<<endl;
		if(i<=tasks.size()&&time==tasks[i].arrival) {
			tasks_queue.push(tasks[i]);			
			//cout<<"top: "<<char(tasks_queue.top().id+64)<<endl;
			i+=1;
		}
		if(!tasks_queue.empty()&&Event.id==-1)
		{
			Event=tasks_queue.top();
			tasks_queue.pop();
		}
		time++;
		if(Event.id!=-1&&Event.cost>0)
		{
			Event.cost--;
			cout<<"正在做："<<char(Event.id+64)<<" "<<"剩余时间："<<Event.cost<<endl;
			if(Event.cost==0)
				{
					cout<<char(Event.id+64)<<" 结束时间为"<<time<<endl; 
					Endtime[Event.id]=time;
					Event.id=-1;
				 } 
		}
		
		if(i>=tasks.size()&&Event.id==-1&&tasks_queue.empty())
		{
				break;	
		}
	}
	cout<<"SJF:"<<endl;
	output();
 } 
void HRRF()
{
	priority_queue<task,vector<task>,cmp_HRRF> tasks_queue;
	task Event(-1,0,0,0);
	int time=0,i=0;
	while(1) {
		cout<<"T:"<<time<<endl; 
		if(i<=tasks.size()&&time==tasks[i].arrival) {
			tasks_queue.push(tasks[i]);			
			cout<<"top: "<<char(tasks_queue.top().id+64)<<endl;
			i+=1;
		}
		if(!tasks_queue.empty()&&Event.id==-1)
		{
			Event=tasks_queue.top();
			tasks_queue.pop();
		}
		time++;
		if(Event.id!=-1&&Event.cost>0)
		{
			Event.cost--;
			cout<<"正在做："<<char(Event.id+64)<<" "<<"剩余时间："<<Event.cost<<endl;
			if(Event.cost==0)
				{
					cout<<char(Event.id+64)<<" 结束时间为"<<time<<endl; 
					Endtime[Event.id]=time;
					time_HRRF=time;
					tasks_queue.push(task(100,0,1,0));
					tasks_queue.pop();
					Event.id=-1;
				 } 
		}
		
		if(i>=tasks.size()&&Event.id==-1&&tasks_queue.empty())
		{
				break;	
		}
	}
	cout<<"HRRF:"<<endl;
	output();
 } 


void RR(int timeslice) {
	cout<<"时间片为："<<timeslice<<endl; 
	priority_queue<task,vector<task>,cmp_FCFS> tasks_queue;
	for(int i=0; i<tasks.size(); i++)
		tasks_queue.push(tasks[i]);
	int time=0;
	while(!tasks_queue.empty()) {
		if(timeslice<tasks_queue.top().cost) {
			cout<<tasks_queue.top()<<" "<<"start: "<<time<<"  "<<"end: "<<time+timeslice<<endl;
			time+=timeslice;
			tasks_queue.push(task(tasks_queue.top().id,time,tasks_queue.top().cost-timeslice,tasks_queue.top().priority));
			tasks_queue.pop();
		} else {
			cout<<tasks_queue.top()<<" "<<"start: "<<time<<"  "<<"end: "<<time+tasks_queue.top().cost<<endl;
			time+=tasks_queue.top().cost;
			Endtime[tasks_queue.top().id]=time;
			tasks_queue.pop();
		}
	}
	cout<<"RR:"<<endl;
	output();
}


void SRTF()
{
	priority_queue<task,vector<task>,cmp_SJF> tasks_queue;
	task Event(-1,0,0,0);
	int time=0,i=0;
	while(1) {
		cout<<"T:"<<time<<endl;
		if(i<=tasks.size()&&time==tasks[i].arrival) {
			tasks_queue.push(tasks[i]);			
			//cout<<"top: "<<char(tasks_queue.top().id+64)<<endl;
			i+=1;
		}
		if(!tasks_queue.empty())
		{
			Event=tasks_queue.top();
//			tasks_queue.pop();
		}
		time++;
		if(Event.id!=-1&&Event.cost>0)
		{
			Event.cost--;
			cout<<"正在做："<<char(Event.id+64)<<" "<<"剩余时间："<<Event.cost<<endl;
			tasks_queue.pop();
			if(Event.cost>0)
				tasks_queue.push(Event);	
			if(Event.cost==0)
				{
					cout<<char(Event.id+64)<<" 结束时间为"<<time<<endl; 
					Endtime[Event.id]=time;
					Event.id=-1;
				 } 
		}
		
		if(i>=tasks.size()&&Event.id==-1&&tasks_queue.empty())
		{
				break;	
		}
	}
	cout<<"SRTF:"<<endl;
	output();
}
int main() {
	init();
//	FCFS();
//	SJF();
	HRRF();
//	RR(4);
//	SRTF();
	return 0;
}

