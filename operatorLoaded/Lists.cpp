#include "Lists.h"
#include<iostream>
#include<iomanip>
Lists::Lists()
{   listHead=new Node;
	listHead->item={"List Head",000000L,0.0};
	listHead->next=NULL;
	pcurrent=listHead;
	nodeCount=0;
}
Lists::~Lists()
{	
	Node*cu=listHead;
	Node* temp;
	while (cu)
	{	
		std::cout<<"delet:  "<<cu<<std::endl;
		temp=cu->next;
		delete cu;
		cu=temp;
	}
std::cout<<"\nThis list has been destored,Bey!";
}

bool Lists::isemtpy() const
{
return nodeCount;
}

bool Lists::isfull()const
{
	return (nodeCount==maxNodeCount);
}

void Lists::show()const
{
	using namespace std;
	cout<<"There all is  "<<nodeCount<<"  Nodes!"<<endl;
	cout<<setw(10)<<"Name"<<setw(18)<<"StudentID"<<setw(12)<<"Score"<<endl;
	cout<<setfill('-')<<setw(40)<<"-"<<setfill(' ')<<endl;
	
	Node *current=listHead;
	while (current->next)
	{
		current=current->next;
		cout<<setw(15)<<current->item.name<<setw(15)<<current->item.studentID
			<<fixed<<ios_base::showpoint<<setprecision(2)<<setw(10)<<current->item.score<<endl;
	}
}

Lists & Lists::operator+(DataType m_item)
{
	if (isfull())
	{
		std::cout<<"The List is full, can't push other item!";
	}
	else
	{
		pcurrent->next=new dataNode;
		pcurrent=pcurrent->next;
		pcurrent->item=m_item;
		pcurrent->next=NULL;
		nodeCount++;
	}
return *this;
}

Lists & operator+( DataType &m_item,Lists &ls)
{
	ls+m_item;
	return ls;
 }

/*
DataType Lists::operator--()
{
DataType temp;
temp=pcurrent->item;


}

*/