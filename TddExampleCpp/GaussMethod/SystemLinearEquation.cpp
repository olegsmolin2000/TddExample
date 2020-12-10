#include "SystemLinearEquation.h"
#include<stdexcept>

LinearEquation& SystemLinearEquation::operator[](int index)
{
	if (index >= 0 && index < system.size())
		return system[index];
	else 
		throw std::out_of_range("");
}

int SystemLinearEquation::size()
{
	return system.size();
}

void SystemLinearEquation::add(LinearEquation& a)
{
	if (a.size() == n + 1)
		system.push_back(a);
	else throw std::invalid_argument("");
}

void SystemLinearEquation::remove()
{
	system.pop_back();
}

void SystemLinearEquation::steppingUp()
{
	int equationForSwapIndex, notNullElementIndex;
	for (int i = 0; i < size(); i++)
	{
		notNullElementIndex = i;

		//���� ������� �� ��������� ����� ����
		if (system[i][notNullElementIndex] == 0)
		{
			//���� ������ �� ������������� ������ ��������� ������� � ���������
			while (system[i][notNullElementIndex] == 0 && notNullElementIndex < n)
				notNullElementIndex++;
			equationForSwapIndex = 1;

			//���� ������ ��������� ��� ������ ������������ ������� �� ����� ����
			while ((i + equationForSwapIndex) < size() && system[i + equationForSwapIndex][notNullElementIndex] == 0)
				equationForSwapIndex++;

			if ((i + equationForSwapIndex) == size())
				return;

			swap(system[i], system[i + equationForSwapIndex]);
		}

		//�������� �� ������ ������ ���� ���� ����� �� ������ ������������� �������� ���� ����
		for (int j = i + 1; j < size(); j++)
		{
			LinearEquation temp1 = system[j] * system[i][notNullElementIndex];
			LinearEquation temp2 = system[i] * system[j][notNullElementIndex];
			system[j] = temp1 - temp2;
		}
	}
}

vector<double> SystemLinearEquation::solveSystem()
{
	//���� ���� ������ �������� ��������� �� ������� ��
	while (system[size() - 1].isNull())
		system.pop_back();

	//���� ��������� ��������� ����� ������
	if (system[size() - 1])
	{
		//���� ���������� ��������� ����� ����������� ����������
		if (size() == n)
		{
			vector<double> solve(n);

			for (int i = size() - 1; i >= 0; i--)
			{
				//����������� ������� ��������� ������� �� ��������� � ���� ������
				// (����������� ��� ����������)
				solve[i] = system[i][n];

				//�������� �� ���� ��� ��������� ����� ���������� �� �������������� ������������
				for (int j = i + 1; j < n; j++)
				{
					solve[i] -= system[i][j] * solve[j];
				}

				//����� �� ����������� ��� ����������� ����������
				solve[i] /= system[i][i];
			}
			return solve;
		}
		else throw std::invalid_argument("any value is solution");
	}
	else throw std::invalid_argument("no solution");
}

SystemLinearEquation::operator std::string()
{
	string res = "";
	for (int i = 0; i < size(); i++)
		res += (string)system[i] + '\n';
	return res;
}