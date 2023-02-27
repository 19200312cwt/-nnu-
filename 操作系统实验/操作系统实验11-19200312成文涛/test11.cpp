#include<vector>
#include<ctime>
#include<random>
#include<cmath>
#include<iostream>
#include<string>
#include <math.h>

using namespace std;

struct work_paragraph
{
	int start;
	int end;
};

struct work
{
	string name;
	vector<work_paragraph> work_place;//页框段
	double size;//长度
	int place_num;//页框总数
};

void add(vector<work_paragraph> w, vector<work_paragraph>&  place)
{//将place按大小顺序添加；
	int j = 0;
	int max = place.back().start;//记录当前内存利用段的最大值
	for (int i = 0; i < w.size(); i++)
	{
		int num = place.size();
		if (w[i].end > max)
		{
			place.push_back(w[i]);
		}
		else
		{
			for (; j < num; j++)
			{//当片段以利用的内存范围内时
				if (w[i].end < place[j].start)
				{//当w的片段在j指向的片段前面时
					place.insert(place.begin() + j, w[i]);//将该数插入
					j++;
					break;
				}
			}
		}
	}
}

int create(vector<work_paragraph>&  place, vector<work>& works,int surplus)
{
	work w;
	work_paragraph gr;
	int start_temp=0, end_temp=0;
	cout << "请输入作业名" << endl;
	cin >>w.name;
	cout << "请输入作业所占字节数" << endl;
	cin >> w.size;
	int sum_num = ceil(w.size / 1000);
	cout<<"sum_num: "<<sum_num<<endl; 
	w.place_num = sum_num;//向上取整
	if (surplus < w.place_num)
	{
		cout << "内存不足，申请失败" << endl;
		return surplus;
	}
	if (place.empty() == true)
	{//当前总内存内没有存内容时
		gr.start = 0;
		gr.end = sum_num-1;
		place.push_back(gr);
		w.work_place.push_back(gr);
		surplus -= w.place_num;
		works.push_back(w);
		cout << "作业内存申请成功" << endl;
		return surplus;
	}
	for (int i = 0; i < place.size(); i++)
	{
		end_temp = place[i].start-1;
		if (start_temp < end_temp)
		{//如果再place的使用片段中有空隙时
			if (end_temp - start_temp < sum_num)
			{
				//当前片段不能满足作业
				gr.start = start_temp;
				gr.end = end_temp;
				w.work_place.push_back(gr);//将该片段加入作业量中
				sum_num = sum_num - end_temp + start_temp-1;
			}
			else
			{
				//当前片段能够满足作业了
				gr.start = start_temp;
				gr.end = start_temp + sum_num-1;
				w.work_place.push_back(gr);
				add(w.work_place,place);//按顺序将内存占用空间加入palce
				surplus -= w.place_num;//将剩余量修改
				works.push_back(w);//将改作业加入作业组中
				cout << "作业内存申请成功" << endl;
				return surplus;//结束循环
			}
		}
		start_temp = place[i].end+1;
	}
	//当循环没有结束，则是没有找到足够满足当前作业的空隙，所以在后面增加
	gr.start = place.back().end + 1;
	gr.end = gr.start + sum_num - 1;
	w.work_place.push_back(gr);
	add(w.work_place, place);
	surplus -= w.place_num;
	works.push_back(w);
	cout << "作业内存申请成功" << endl;
	return surplus;
}

int  reclaim(vector<work_paragraph>& place, vector<work>& works, int surplus)
{
	work w;
	cout << "请输入作业名" << endl;
	cin >> w.name;
	for (int i = 0; i < works.size(); i++)
	{
		if (works[i].name == w.name)
		{
			w = works[i];
			//找到了作业名
			int address = 0;
			for (int j = 0; j < w.work_place.size(); j++)
			{
				while (true)
				{
					if (place[address].start==w.work_place[j].start&&place[address].end==w.work_place[j].end)
					{
						place.erase(place.begin() + address);
						break;
					}
					address++;
				}
			}
			works.erase(works.begin()+i);//删除作业列表中的元素；
			surplus += w.place_num;
			return surplus;
		}
	}
	//没有找到作业
	cout << "没有找到该作业" << endl;
	return surplus;
}

void show(vector<work_paragraph>& place, vector<work>& works, int surplus)
{
	cout << "内存分配情况如下：" << endl;
	if (works.size() == 0)
	{
		cout << "目前没有作业占用内存" << endl;
		return;
	}
	else
	{
		cout << "作业名称  " << "占用页框数  " << "占用页框号 " << endl;
		for (int i = 0; i < works.size(); i++)
		{
			cout << works[i].name << "     ";
			cout << works[i].place_num << "    ";
			for (int j = 0; j < works[i].work_place.size(); j++)
			{
				cout << works[i].work_place[j].start << "-" << works[i].work_place[j].end << "  ";
			}
			cout << endl;
		}
		cout << surplus << endl;
	}
}

void visit(vector<work_paragraph>& place, vector<work>& works, int surplus)
{
	work w;
	cout << "请输入你想要访问的作业名：" << endl;
	cin >> w.name;
	for (int i = 0; i < works.size(); i++)
	{
		if (works[i].name == w.name)
		{
			w = works[i];
			//找到了作业名
			int path;
			cout << "请输入逻辑访问地址：" << endl;
			cin >> path;
			if (path > w.size)
			{
				cout << "访问越界！！！" << endl;
				return;
			}
			int path_num = ceil(path / 1000);//向上取整
			int offset_path = path % 1000;//偏移量
			for (int j = 0; j < w.work_place.size(); j++)
			{
				int num = w.work_place[j].end - w.work_place[j].start;
				if (num < path_num)
				{//当前片段不包括访问页框
					path_num -= num;
				}
				else
				{//当前片段包括访问页框
					cout << "访问第" << w.work_place[j].start + path_num << "号页框";
					if (offset_path != 0)
					{
						cout << ",偏移量为：" << offset_path;
					}
					cout << endl;
					return;
				}
			}
			cout << "访问第" << w.work_place.back().start + path_num << "号页框";
			if (offset_path != 0)
			{
				cout << ",偏移量为：" << offset_path;
			}
			cout << endl;
			return;
		}
	}
	//没有找到作业
	cout << "没有找到该作业" << endl;
	return;
}

void menu()
{
	cout << "1.分配内存\n"
		<< "2.回收内存\n"
		<< "3.显示内存分配\n"
		<< "4.访问内存\n"
		<< "0.退出" << endl;
	cout << "\n请选择：";
}

int main() {
	vector<work> works;//总的作业
	vector<work_paragraph>  place;//总的内存段
	int surplus = 100;//剩余的内存数
	int choose;
	menu();
	cin >> choose;
	while (choose != 0) {
		switch (choose) {
		case 1:
			surplus=create(place,works,surplus);
			break;
		case 2:
			surplus=reclaim(place, works, surplus);
			break;
		case 3:
			show(place, works, surplus);
			break;
		case 4:
			visit(place, works, surplus);
		default:
			break;
		}
		menu();
		cin >> choose;
	}
}

