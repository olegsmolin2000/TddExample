#pragma once
class IndexerCpp
{
private:
	double* arr;
	int begin;
	int length;

	//проверка на корректность аргументов при вызове конструктора
	bool CheckArguments(int arrayLength, int beginIndex, int indexerLength);
	//проверка корректности введённого индекса
	bool CheckIndex(int, int, int);

public:
	IndexerCpp(double* array, int arrayLength, int beginIndex, int indexerLength);
	~IndexerCpp() {}

	int getLength() { return length; }

	//перегрузка оператора взятия элемента по ссылке
	double& operator[] (int index);
	
};

