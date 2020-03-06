#pragma once
#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer
{
private:
		long when;
		int protime;
		int protimeMax;
public:
	Customer(){when=protime=0,protimeMax=3;}
	long arrive()const {return when;}
	int fprotime()const{return protime;}
	void set(const long  m_when,const int m_protimeMax);
};

#endif // !CUSTOMER_H_
