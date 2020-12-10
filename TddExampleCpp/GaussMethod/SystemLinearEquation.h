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

	LinearEquation& operator[] (int index);//перегрузка оператора взятия элемента по ссылке
	int size();

	void add(LinearEquation&);
	void remove();

	void steppingUp();//приведение системы к ступеньчатому виду
	vector<double> solveSystem();//решение системы

	operator std::string();//перегрузка приведения к строчному типу
};

