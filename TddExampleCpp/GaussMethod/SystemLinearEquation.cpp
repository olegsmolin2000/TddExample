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

		//если элемент на диагонали равен нулю
		if (system[i][notNullElementIndex] == 0)
		{
			//ищем справа от диагонального первый ненулевой элемент в уравнении
			while (system[i][notNullElementIndex] == 0 && notNullElementIndex < n)
				notNullElementIndex++;
			equationForSwapIndex = 1;

			//ищем первое уравнение где нужный диагональный элемент не равен нулю
			while ((i + equationForSwapIndex) < size() && system[i + equationForSwapIndex][notNullElementIndex] == 0)
				equationForSwapIndex++;

			if ((i + equationForSwapIndex) == size())
				return;

			swap(system[i], system[i + equationForSwapIndex]);
		}

		//вычитаем из каждый строки нашу чтоб снизу от нашего диагонального элемента были нулю
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
	//если есть пустые линейные уравнения то удаляем их
	while (system[size() - 1].isNull())
		system.pop_back();

	//если последнее уравнение можно решить
	if (system[size() - 1])
	{
		//если количество уравнений равно количествку переменных
		if (size() == n)
		{
			vector<double> solve(n);

			for (int i = size() - 1; i >= 0; i--)
			{
				//присваиваем решению последний элемент из уравнения в этой строке
				// (коэффициент без переменной)
				solve[i] = system[i][n];

				//вычитаем из него все найденные корни умноженные на соответсвующие коэффициенты
				for (int j = i + 1; j < n; j++)
				{
					solve[i] -= system[i][j] * solve[j];
				}

				//делим на коэффициент при вычисляемой переменной
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