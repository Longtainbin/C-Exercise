// Author: Long Tianbin
// Created Date: 2020-8-26
//排序方法比较

#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

void insertSort(vector<int> &v,size_t Lef,size_t Rig);
void heapSort(vector<int>& v);
void quickSortSub(vector<int>& v,int Lef,int Rig);
void quickSort(vector<int>& v);

int main()
{   
std::random_device rd;
std::default_random_engine e(rd());
std::uniform_int_distribution<int> dis(-1000,1000);
int N=10000;
vector<int> v(N);
std::for_each(v.begin(),v.end(),[&](int &x){x=dis(e);});
//vector<int> v({3,3,3,3,3,3,8,3,3,3,3,3,3,3});
auto v2=v;
auto v3=v;

cout<<"N="<<N<<'\n';

auto start = std::chrono::system_clock::now();
quickSort(v);
auto end = std::chrono::system_clock::now();
std::chrono::duration<double> elapsed_seconds=(end-start);
cout<<"快速排序运行："<<elapsed_seconds.count()<<" s"<<'\n';


start = std::chrono::system_clock::now();
heapSort(v3);
end = std::chrono::system_clock::now();
elapsed_seconds=(end-start);
cout<<"堆排序运行："<<elapsed_seconds.count()<<" s"<<'\n';

start = std::chrono::system_clock::now();
insertSort(v2,0,v2.size()-1);
end = std::chrono::system_clock::now();
elapsed_seconds=(end-start);
cout<<"插入排序运行："<<elapsed_seconds.count()<<" s"<<'\n';

}

/*插入排序*/
void insertSort(vector<int> &v,size_t Lef,size_t Rig)
{
auto N=Rig-Lef+1;
if(N>1)
{ 
int temp=0;
for (size_t i = Lef+1; i <=Rig; ++i)
{
	for (size_t j = Lef; j<i; ++j)
	{		
		if(v[i]<v[j])
		{
			temp=v[i];
			v[i]=v[j];
			v[j]=temp;
		}
	}
}
}
}
/*堆排序*/
void heapSort(vector<int>& v)
{
	std::priority_queue<int,vector<int>,std::greater<int>>pq;
	std::for_each(v.begin(),v.end(),[&pq](int x){pq.push(x);});
	std::for_each(v.begin(),v.end(),[&pq](int &x){x=pq.top();pq.pop();});
}

/*快速排序*/
void quickSort(vector<int>& v)
{
int Lef=0,Rig=v.size()-1;
quickSortSub(v,Lef,Rig);
}

void quickSortSub(vector<int>& v,int Lef,int Rig)
{
	if ((Rig-Lef)>10)
	{
	//选取枢纽元(三数中值)
	int Cen=(Lef+Rig)/2;
	if(v[Lef]>v[Cen])
		swap(v[Lef],v[Cen]);
	if(v[Lef]>v[Rig])
		swap(v[Lef],v[Rig]);
	if(v[Cen]>v[Rig])
		swap(v[Cen],v[Rig]);
	int temp=v[Cen];
	swap(v[Cen],v[Rig]);
	//分割
	int i=Lef,j=Rig-1;
	while (i<=j)
	{
		if(v[i]<temp)
			++i;
		else
		{
			if(v[j]>temp)
				--j;
			else 
				{
				 swap(v[i],v[j]);	
					++i;--j;
				}
		}	
	}
	swap(v[i],v[Rig]);
	
	//递归
	quickSortSub(v,Lef,i-1);
	quickSortSub(v,i+1,Rig);
	
	}
	else
	{
		insertSort(v,Lef,Rig);
	}
}