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

	//перегрузка конструктора копирования и оператора присваивания по ссылке
	LinearEquation(const LinearEquation&);
	LinearEquation& operator=(const LinearEquation&);

	~LinearEquation() { vector<double>().swap(koeffs); };

	double& operator[] (int index);//перегрузка оператора взятия элемента по ссылке

	int size() { return koeffs.size(); }

	//заполнение уравнения случайными или одинаковыми числами
	void FillRandomValues();
	void FillSameValues(double);

	//перегрузки операторов арфиметических действий
	LinearEquation operator+(LinearEquation&);
	LinearEquation operator-(LinearEquation&);
	LinearEquation operator*(const double&);
	friend LinearEquation operator*(double, LinearEquation&);
	LinearEquation operator-();

	//перегрузки преобразований в другие типы
	operator string();
	operator vector<double>();
	operator bool();

	//перегрузки операторов сравнения
	bool operator==(const LinearEquation&);
	bool operator!=(const LinearEquation&);

	//проверка на пустоту уравнения
	bool isNull();
};