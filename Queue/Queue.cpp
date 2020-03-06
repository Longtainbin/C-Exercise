#include "Queue.h"
#include<iostream>

Queue::Queue(int m_nodecount):qsize(m_nodecount)
{
front=nullptr;
rear=nullptr;
nodecount=0;

}

Queue::~Queue()
{
	Node *temp;
	while (front)
	{
		temp = front;
		front=front->next;
		//std::cout<<"Delete "<<"  ItemAdress: "<<temp<<std::endl;
		delete temp;
	}
}

int Queue::queuecount()
{
	int count=0;
	Node * temp=front;
	while (temp)
	{
		count++;
		temp=temp->next;
	}
return count;
}

bool Queue::isfull()
{
return queuecount()>=qsize;
}

bool Queue::isempty()
{
	return front==nullptr;
}

bool Queue::enqueue(const Item &m_item)
{
if(isfull())
	{
	std::cout<<"The Queue is overdull!\n";
	return false;
	}
Node * additem=new Node;
additem->next=nullptr;
additem->item=m_item;
nodecount++;
//std::cout<<"Creat # "<<nodecount<<"  ItemAdress: "<<additem<<std::endl;
if(front==nullptr)
	front=additem; 
else
	rear->next=additem;
rear=additem;
return true;
}

bool Queue::dequeue(Item& m_item)
{
	if (isempty())
		return false;
	m_item=front->item;
	nodecount--;
	Node *temp=front;
	front=front->next;
	//std::cout<<"Delete "<<"  ItemAdress: "<<temp<<std::endl;
	delete temp;
	return true;
}

void Queue::showqueue()
{	using namespace std;
	if(front==nullptr)
		cout<<"There is a emtpy queue!\n";
	else
	{
	int count=0;
	Node * temp=front;
	while (temp)
	{
		count++;
		cout<<"# "<<count<<"  Item When is: "<<temp->item.arrive()<<endl;
		temp=temp->next;
	}
	}
}