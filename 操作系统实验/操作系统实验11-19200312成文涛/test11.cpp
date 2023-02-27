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
	vector<work_paragraph> work_place;//ҳ���
	double size;//����
	int place_num;//ҳ������
};

void add(vector<work_paragraph> w, vector<work_paragraph>&  place)
{//��place����С˳����ӣ�
	int j = 0;
	int max = place.back().start;//��¼��ǰ�ڴ����öε����ֵ
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
			{//��Ƭ�������õ��ڴ淶Χ��ʱ
				if (w[i].end < place[j].start)
				{//��w��Ƭ����jָ���Ƭ��ǰ��ʱ
					place.insert(place.begin() + j, w[i]);//����������
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
	cout << "��������ҵ��" << endl;
	cin >>w.name;
	cout << "��������ҵ��ռ�ֽ���" << endl;
	cin >> w.size;
	int sum_num = ceil(w.size / 1000);
	cout<<"sum_num: "<<sum_num<<endl; 
	w.place_num = sum_num;//����ȡ��
	if (surplus < w.place_num)
	{
		cout << "�ڴ治�㣬����ʧ��" << endl;
		return surplus;
	}
	if (place.empty() == true)
	{//��ǰ���ڴ���û�д�����ʱ
		gr.start = 0;
		gr.end = sum_num-1;
		place.push_back(gr);
		w.work_place.push_back(gr);
		surplus -= w.place_num;
		works.push_back(w);
		cout << "��ҵ�ڴ�����ɹ�" << endl;
		return surplus;
	}
	for (int i = 0; i < place.size(); i++)
	{
		end_temp = place[i].start-1;
		if (start_temp < end_temp)
		{//�����place��ʹ��Ƭ�����п�϶ʱ
			if (end_temp - start_temp < sum_num)
			{
				//��ǰƬ�β���������ҵ
				gr.start = start_temp;
				gr.end = end_temp;
				w.work_place.push_back(gr);//����Ƭ�μ�����ҵ����
				sum_num = sum_num - end_temp + start_temp-1;
			}
			else
			{
				//��ǰƬ���ܹ�������ҵ��
				gr.start = start_temp;
				gr.end = start_temp + sum_num-1;
				w.work_place.push_back(gr);
				add(w.work_place,place);//��˳���ڴ�ռ�ÿռ����palce
				surplus -= w.place_num;//��ʣ�����޸�
				works.push_back(w);//������ҵ������ҵ����
				cout << "��ҵ�ڴ�����ɹ�" << endl;
				return surplus;//����ѭ��
			}
		}
		start_temp = place[i].end+1;
	}
	//��ѭ��û�н���������û���ҵ��㹻���㵱ǰ��ҵ�Ŀ�϶�������ں�������
	gr.start = place.back().end + 1;
	gr.end = gr.start + sum_num - 1;
	w.work_place.push_back(gr);
	add(w.work_place, place);
	surplus -= w.place_num;
	works.push_back(w);
	cout << "��ҵ�ڴ�����ɹ�" << endl;
	return surplus;
}

int  reclaim(vector<work_paragraph>& place, vector<work>& works, int surplus)
{
	work w;
	cout << "��������ҵ��" << endl;
	cin >> w.name;
	for (int i = 0; i < works.size(); i++)
	{
		if (works[i].name == w.name)
		{
			w = works[i];
			//�ҵ�����ҵ��
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
			works.erase(works.begin()+i);//ɾ����ҵ�б��е�Ԫ�أ�
			surplus += w.place_num;
			return surplus;
		}
	}
	//û���ҵ���ҵ
	cout << "û���ҵ�����ҵ" << endl;
	return surplus;
}

void show(vector<work_paragraph>& place, vector<work>& works, int surplus)
{
	cout << "�ڴ����������£�" << endl;
	if (works.size() == 0)
	{
		cout << "Ŀǰû����ҵռ���ڴ�" << endl;
		return;
	}
	else
	{
		cout << "��ҵ����  " << "ռ��ҳ����  " << "ռ��ҳ��� " << endl;
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
	cout << "����������Ҫ���ʵ���ҵ����" << endl;
	cin >> w.name;
	for (int i = 0; i < works.size(); i++)
	{
		if (works[i].name == w.name)
		{
			w = works[i];
			//�ҵ�����ҵ��
			int path;
			cout << "�������߼����ʵ�ַ��" << endl;
			cin >> path;
			if (path > w.size)
			{
				cout << "����Խ�磡����" << endl;
				return;
			}
			int path_num = ceil(path / 1000);//����ȡ��
			int offset_path = path % 1000;//ƫ����
			for (int j = 0; j < w.work_place.size(); j++)
			{
				int num = w.work_place[j].end - w.work_place[j].start;
				if (num < path_num)
				{//��ǰƬ�β���������ҳ��
					path_num -= num;
				}
				else
				{//��ǰƬ�ΰ�������ҳ��
					cout << "���ʵ�" << w.work_place[j].start + path_num << "��ҳ��";
					if (offset_path != 0)
					{
						cout << ",ƫ����Ϊ��" << offset_path;
					}
					cout << endl;
					return;
				}
			}
			cout << "���ʵ�" << w.work_place.back().start + path_num << "��ҳ��";
			if (offset_path != 0)
			{
				cout << ",ƫ����Ϊ��" << offset_path;
			}
			cout << endl;
			return;
		}
	}
	//û���ҵ���ҵ
	cout << "û���ҵ�����ҵ" << endl;
	return;
}

void menu()
{
	cout << "1.�����ڴ�\n"
		<< "2.�����ڴ�\n"
		<< "3.��ʾ�ڴ����\n"
		<< "4.�����ڴ�\n"
		<< "0.�˳�" << endl;
	cout << "\n��ѡ��";
}

int main() {
	vector<work> works;//�ܵ���ҵ
	vector<work_paragraph>  place;//�ܵ��ڴ��
	int surplus = 100;//ʣ����ڴ���
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

