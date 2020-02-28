#pragma once
#ifndef LISTS_H_
#define LISTS_H_

#include<string>

struct DataType
{
	std::string name;
	long studentID;
	double score;
};

struct dataNode
{
	DataType item;
	dataNode* next;
};

typedef dataNode Node;

class Lists
{
private:
		Node* listHead;
		Node* pcurrent;
		int nodeCount;
		static const int maxNodeCount=100;
public:
		Lists();
		~Lists();
		
		Lists & operator+(DataType m_item);//���
		friend Lists & operator+(DataType &m_item,Lists &ls);
		//DataType operator--();//����
		
		bool isemtpy()const;
		bool isfull()const;
		void show() const;
};

#endif // !LISTS_H_