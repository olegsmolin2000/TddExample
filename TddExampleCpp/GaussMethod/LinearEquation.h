#pragma once
#include<vector>
#include<string>

using namespace std;

class LinearEquation
{
public:
	vector<double> koeffs;
public:
	LinearEquation(string);
	LinearEquation(double*,int);
	LinearEquation(vector<double>);
	LinearEquation(int);

	//���������� ������������ ����������� � ��������� ������������ �� ������
	LinearEquation(const LinearEquation&);
	LinearEquation& operator=(const LinearEquation&);

	~LinearEquation() { vector<double>().swap(koeffs); };

	double& operator[] (int index);//���������� ��������� ������ �������� �� ������

	int size() { return koeffs.size(); }

	//���������� ��������� ���������� ��� ����������� �������
	void FillRandomValues();
	void FillSameValues(double);

	//���������� ���������� �������������� ��������
	LinearEquation operator+(LinearEquation&);
	LinearEquation operator-(LinearEquation&);
	LinearEquation operator*(const double&);
	friend LinearEquation operator*(double, LinearEquation&);
	LinearEquation operator-();

	//���������� �������������� � ������ ����
	operator string();
	operator vector<double>();
	operator bool();

	//���������� ���������� ���������
	bool operator==(const LinearEquation&);
	bool operator!=(const LinearEquation&);

	//�������� �� ������� ���������
	bool isNull();
};