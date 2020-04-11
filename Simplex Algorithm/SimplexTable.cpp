#include "SimplexTable.h"
#include <iostream>
#include<iomanip>
#include<algorithm>
#include<iterator>
#include<set>
#include<vector>
#include<Eigen/Dense>
#include<Eigen/LU>
using namespace std;
using namespace Eigen;

SimplexTable::SimplexTable(const RowVectorXd & Cf, const MatrixXd & Af, const VectorXd & bf, const RowVectorXi & baseSetf)
	:C(Cf),A(Af),b(bf), baseSetff(baseSetf), mRow(bf.size()),nCol(Cf.size())
	{
	
	}
void SimplexTable::init()
{
	for (uint32_t i = 0; i < baseSetff.size(); ++i)
		baseSet.push_back(baseSetff(i)-1);
	vector<uint32_t> baseTotal;
	for (uint32_t i = 0; i < nCol; ++i)
		baseTotal.push_back(i);
	set_difference(baseTotal.begin(), baseTotal.end(), baseSet.begin(), baseSet.end(), back_inserter(noBaseSet));

	bx.resize(mRow);
	r.resize(nCol);
	y.resize(mRow, nCol);
	B.resize(mRow, mRow);
	CB.resize(mRow);
}

void SimplexTable::caculateValue()
{
	//计算基变量的值
	for (uint32_t i = 0; i < mRow; ++i)
	{
		B.col(i) = A.col(baseSet.at(i));
		CB(i) = C(baseSet[i]);
		y.col(baseSet[i]) = MatrixXd::Zero(mRow, 1);
		y(i, baseSet[i]) = 1;
		r(baseSet[i]) = 0;
	}

	//计算非基变量的值
	for (uint32_t i = 0; i < nCol-mRow; ++i)
	{
		y.col(noBaseSet[i]) = B.lu().solve(A.col(noBaseSet[i]));
		r(noBaseSet[i]) = C(noBaseSet[i]) - CB.dot(y.col(noBaseSet[i]));
	}
	bx = B.lu().solve(b);
	f = -CB.dot(bx);
}

bool SimplexTable::isOptimal()
{
	return !((r.array()<0).any());
}

void SimplexTable::exchangeBase()
{
	uint32_t  k;	//进基
	r.minCoeff(&k );
	//判断是否无界
	if ((y.col(k).array() < 0).all())
	{
		string str = "所求无界!!!\n";
		throw(str);
		//cout << "\n所求表达式无界!!!\n";
		//exit(EXIT_FAILURE);
	}

	uint32_t big0 = (y.col(k).array() > 0).count();
	vector<uint32_t> bx_y_index;
	vector<double> bx_y;

	for (uint32_t i = 0; i < mRow; ++i)
	{
		if (y(i, k) > 0)
		{
			bx_y.push_back(bx(i)/y(i,k));
			bx_y_index.push_back(i);
		}
	}
	 

	uint32_t t_i = bx_y_index.at(min_element(bx_y.begin(), bx_y.end()) - bx_y.begin());
	uint32_t t = baseSet.at(t_i); // t为出基


	//变基
	baseSet[t_i] = k;
	for (uint32_t i=0;i< nCol-mRow;++i)
	{
		if (noBaseSet[i] == k)
		{
			noBaseSet[i] = t;
			break;
		}
	}
	
}

void SimplexTable::outOptimalResult(ostream & os)
{
	os << "最优目标值：" << f<<endl;
	os << "最优解：" << endl;
	
	for (uint32_t i = 0; i < mRow; ++i)
	{
		os << setw(6)<<"X_" << baseSet[i]+1 << "    " << bx(i) << endl;
	}

	for (uint32_t i = 0; i < nCol-mRow; ++i)
	{
		os << setw(6)  << "X_" << noBaseSet[i]+1 << "    " <<0 << endl;
	}
}

ostream & operator<<(ostream & os, const SimplexTable & st)
{
	os << "单纯行表：" << endl;
	uint8_t chS = 4;
	uint8_t chS2 = 8;

	os << setw(chS2) << "XB" << setw(chS) << ' ';
	for (uint32_t i = 0; i < st.nCol; ++i)
	{
		os << setw(chS2)<< "X_" << i + 1 << setw(chS) << ' ';
	}
	os << setw(chS2)  << "bx" << endl;
	for (uint32_t i = 0; i < st.mRow; ++i)
	{
		for (uint32_t j = 0; j < st.nCol+2; ++j)
		{
			if (j == 0)
				os << setw(chS2) << "X_" << st.baseSet[i]+1 << setw(chS) << ' ';
			else if(j== st.nCol + 1)
			{
				os << setw(chS2) << st.bx(i) <<setw(chS) << ' ' << endl;
			}
			else
			{
				os << setw(chS2) << st.y(i, j-1)<<setw(chS) << ' ';
			}
		}

	}
	for (uint32_t j = 0; j < st.nCol + 2; ++j)
	{
		if (j == 0)
			os << setw(chS2) << "r" <<  setw(chS) << ' ';
		else if (j == st.nCol + 1)
		{
			os << setw(chS2) <<  st.f << setw(chS) << ' ' << endl;
		}
		else
		{
			os << setw(chS2)  << st.r(j) << setw(chS) << ' ';
		}
	}

	os << endl;
	return os;
}