#include "Customer.h"
#include<cstdlib>

void Customer::set(const long m_when,const int m_protimeMax)
{
	when=m_when;
	protime=std::rand()%m_protimeMax+1;
}