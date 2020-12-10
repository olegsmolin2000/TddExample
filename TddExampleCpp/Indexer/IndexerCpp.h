#pragma once
class IndexerCpp
{
private:
	double* arr;
	int begin;
	int length;

	//�������� �� ������������ ���������� ��� ������ ������������
	bool CheckArguments(int arrayLength, int beginIndex, int indexerLength);
	//�������� ������������ ��������� �������
	bool CheckIndex(int, int, int);

public:
	IndexerCpp(double* array, int arrayLength, int beginIndex, int indexerLength);
	~IndexerCpp() {}

	int getLength() { return length; }

	//���������� ��������� ������ �������� �� ������
	double& operator[] (int index);
	
};

