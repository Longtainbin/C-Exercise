//适用如下形式的线性规划：
// Object:  min f= C'X
// s.t.  :  AX=b,
//			X>=0.
// 注意：应当使 b>=0 ，C'的单引号表示其为行向量
#pragma once

#include <iostream>
#include<set>
#include<vector>
#include<Eigen/Dense>

using namespace std;
using namespace Eigen;

class SimplexTable
{
using uint32_t =	Eigen::Index ;
private:
	uint32_t mRow;	//约束条件个数 （即 size(b)）
	uint32_t nCol;	//变量总个数	（即 size(X)）
	RowVectorXd C;
	//VectorXd X;
	MatrixXd A;
	VectorXd b;

	RowVectorXi baseSetff;
	vector<uint32_t> baseSet;//基变量
	vector<uint32_t> noBaseSet;
	
	double f;	//目标值
	VectorXd bx;
	RowVectorXd r;//校验数
	MatrixXd y;
	MatrixXd B;
	RowVectorXd CB;
	
public:
	SimplexTable(const RowVectorXd & Cf,const MatrixXd & Af, const VectorXd & bf, const RowVectorXi & baseSetf);
	
	void init();

	void caculateValue();

	bool isOptimal();

	void exchangeBase();

	void outOptimalResult(ostream & os);

	friend ostream & operator<<(ostream & os, const SimplexTable & st);
};

