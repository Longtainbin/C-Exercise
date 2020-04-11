//单纯行法求解标准线性规划的实现
//适用如下形式的线性规划：
// Object:  min f= C'X
// s.t.  :  AX=b,
//			X>=0.
// 注意：应当使 b>=0 ，C'的单引号表示其为行向量
// 2020/4/11  By Tianbin Long

#include<iostream>

#include<Eigen/Dense>
#include "SimplexTable.h"
#include<stdexcept>
using namespace std;
using namespace Eigen;

void checkCorret(const RowVectorXd & Cf, const MatrixXd & Af, const VectorXd & bf, const RowVectorXi & baseSetf);


int main()
{
	
	RowVectorXd C;
	VectorXd b;
	RowVectorXi  baseSet;//指标从 1 开始，因为在SimplexTable.init()中会减 1
	MatrixXd A;
	
	int m = 3;
	int n = 6;

	C.resize(n);
	b.resize(m);
	baseSet.resize(m);
	A.resize(m, n);

	C << -1, -2, -3;
	
	A << 1, 2, 3, 1, 0, 0,
		 1, 1, 0, 0, 1, 0,
		 1, 0, 0, 0, 0, 1;
		
	b << 10,5,1;
	baseSet << 3,2,6;

	checkCorret(C, A, b, baseSet);
	SimplexTable simplexT(C,A,b,baseSet);
	simplexT.init();

	uint32_t iterCout = 0;
	uint32_t iterMaxCout = 10000;

	while (iterCout< iterMaxCout)
	{

		++iterCout;
		
		simplexT.caculateValue();
		//cout<<"第"<<iterCout<<"迭代"<<endl;
		//cout << simplexT;

		if (simplexT.isOptimal())
		{
			break;
		}

		try 
		{
			simplexT.exchangeBase();
		}
		catch(string & str)
		{
			cout << str << endl;
			exit(EXIT_FAILURE);
		}
		catch (out_of_range & e)
		{
			cout << e.what() << endl;
			exit(EXIT_FAILURE);

		}
		catch (length_error & e)
		{
			cout << e.what() << endl;
			exit(EXIT_FAILURE);

		}
		catch (invalid_argument & e)
		{
			cout << e.what() << endl;
			exit(EXIT_FAILURE);

		}
		catch (range_error & e)
		{
			cout << e.what() << endl;
			exit(EXIT_FAILURE);

		}
	}


	simplexT.outOptimalResult(cout);
	cout << simplexT;

	system("pause");
	return  0;
}

void checkCorret(const RowVectorXd & Cf, const MatrixXd & Af, const VectorXd & bf, const RowVectorXi & baseSetf)
{
	try {

		if (Af.cols() <= Af.rows())
		{
			throw( "矩阵 A 的行数必须小于列数\n");			
		}

		if (Af.cols()!=Cf.size()|| Af.rows()!=bf.size())
		{
			throw( "矩阵 A 的行数必须等于 向量b 的列数，A的列数必须等于 行向量C 的行数\n");
		}

		if (!(bf.array() >= 0).all())
		{
			throw("向量b的值应当大于 0\n");
		}

	}

	catch (char *str)
	{
		cout << str;
		exit(EXIT_FAILURE);
	}

}