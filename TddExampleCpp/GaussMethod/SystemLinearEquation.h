#pragma once
#include"LinearEquation.h"
#include<string>
class SystemLinearEquation
{
private:
	vector<LinearEquation> system;
	int n;
public:
	SystemLinearEquation(int n):n(n){}
	~SystemLinearEquation() { vector<LinearEquation>().swap(system); }

	LinearEquation& operator[] (int index);//���������� ��������� ������ �������� �� ������
	int size();

	void add(LinearEquation&);
	void remove();

	void steppingUp();//���������� ������� � ������������� ����
	vector<double> solveSystem();//������� �������

	operator std::string();//���������� ���������� � ��������� ����
};

