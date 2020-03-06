
#include<iostream>
#include <string>
#include<ctime>
#include<fstream>
#include<cstdlib>

#include"Queue.h"
using namespace std;

bool newcustomer(double );

const int MIN_PRE_HOU =60;

int main()
{   
using std::cin;
using std::cout;
using std::endl;
using std::ios_base;
std::srand((unsigned int)time(0));
cout<<"输入 g:继续      q:退出"<<endl;
char ch=0;
while(cin>>ch&&ch!='q')
{
cin.clear();
while(cin.get()!='\n')
	continue;

cout<<"模拟排队场景"<<endl;
//参数输入
cout<<"请输入队列的长度:";
int qs=1;
while (! (cin >> qs))
{
    cin.clear();
	while (cin.get()!='\n')
				continue;
	
	cout<<"请输入队列的长度:";
}

cout<<"请输入仿真时长:";
int hours;
while (! (cin >> hours))
{
    cin.clear();
	while (cin.get()!='\n')
	{
		continue;
	}
	cout<<"请输入仿真时长:";
}

cout<<"请输入单位时间客户数目:";
double prehour;
while (! (cin >> prehour))
{
    cin.clear();
	while (cin.get()!='\n')
	{
		continue;
	}
	cout<<"请输入单位时间客户数目:";
}

cout<<"请输入客户最长处理时间:";
int ptimemax;
while (! (cin >> ptimemax))
{
    cin.clear();
	while (cin.get()!='\n')
	{
		continue;
	}
	cout<<"请输入客户最长处理时间:";
}

//参数输入

//初始化参数
Queue line(qs);
long cyclelimit=MIN_PRE_HOU*hours;
double min_pre_cust=MIN_PRE_HOU/prehour;

Item temp;
long turnaways=0;
long customters=0;
long served=0;
long sum_line=0;
int wait_time=0;
long wait_line=0;

for (int cycle = 0; cycle < cyclelimit; cycle++)
{
	if (newcustomer(min_pre_cust))
	{
		if(line.isfull())
			turnaways++;
		else
		{
			customters++;
			temp.set(cycle,ptimemax);
			line.enqueue(temp);
		}		
	}
	if (wait_time <= 0 && !line.isempty())
	{
		line.dequeue(temp);
		wait_time=temp.fprotime();
		wait_line+=cycle-temp.arrive();
		served++;
	}
	if(wait_time>0)
		wait_time--;
sum_line+=line.queuecount();

}
if (customters > 0)
{
cout<<"总共客户:"<<customters<<endl;
cout<<"已服务客户:"<<served<<endl;
cout<<"被抛弃客户:"<<turnaways<<endl;
cout<<"平均队列长度:";
cout.precision(4);
cout.setf(ios_base::fixed,ios_base::floatfield);
cout<<(double)sum_line/cyclelimit<<endl;
cout<<"平均等待时间:"<<(double)wait_line/served<<endl;
}
else
{
	cout<<"没人来！！！\n";
}
cout<<"完成！\n";

cout<<"输入 g:继续      q:退出"<<endl;
}
    return 0;
}


bool newcustomer(double x)
{
	return (std::rand()*x/RAND_MAX<1);
}