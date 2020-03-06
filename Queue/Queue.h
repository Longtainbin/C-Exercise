#pragma once
#ifndef QUEUE_H_
#define QUEUE_H_
#include "Customer.h"

typedef Customer Item;

class Queue
{
private:
	struct Node
	{
		Item item;
		Node * next;
	};
	enum{QSIZE=10};
	
	Node * front;
	Node * rear;
	int nodecount;
	const int qsize;
public:
		Queue(int m_nodecount=QSIZE);
		~Queue();
		bool isfull();
		bool isempty();
		int queuecount();
		bool enqueue(const Item &m_item);
		bool dequeue(Item &m_item);
		void showqueue();
};

#endif // !QUEUE_H_
