//����������ʽ�����Թ滮��
// Object:  min f= C'X
// s.t.  :  AX=b,
//			X>=0.
// ע�⣺Ӧ��ʹ b>=0 ��C'�ĵ����ű�ʾ��Ϊ������
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
	uint32_t mRow;	//Լ���������� ���� size(b)��
	uint32_t nCol;	//�����ܸ���	���� size(X)��
	RowVectorXd C;
	//VectorXd X;
	MatrixXd A;
	VectorXd b;

	RowVectorXi baseSetff;
	vector<uint32_t> baseSet;//������
	vector<uint32_t> noBaseSet;
	
	double f;	//Ŀ��ֵ
	VectorXd bx;
	RowVectorXd r;//У����
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

