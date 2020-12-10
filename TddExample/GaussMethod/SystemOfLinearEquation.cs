using System;
using System.Collections.Generic;
using System.Text;

namespace GaussMethod
{
    public class SystemOfLinearEquation
    {
        private List<LinearEquation> system;
        private int n;

        public int size => this.system.Count;

        public SystemOfLinearEquation(int n)
        {
            this.n = n;
            system = new List<LinearEquation>();
        }

        public LinearEquation this[int index]
        {
            get
            {
                if (index >= 0 && index < size)
                    return this.system[index];
                else
                    throw new IndexOutOfRangeException();
            }
            set
            {
                if (index >= 0 && index < size) {
                    if (value.Size == this.n+1)
                        this.system[index] = value;
                    else
                        throw new ArgumentException();
                    }
                else
                    throw new IndexOutOfRangeException();
            }
        }

        public void add(LinearEquation equation)
        {
            if (equation.Size == n+1)
                system.Add(equation);
            else
                throw new ArgumentException();
        }

        public static bool operator ==(SystemOfLinearEquation a,SystemOfLinearEquation b)
        {
            //если размеры не равны то точно разные
            if (a.size != b.size || a.n != b.n) 
                return false;
            else
            {
                for (int i = 0; i < a.size; i++)
                {
                    if (a.system[i] != b.system[i])
                        return false;
                }
            }
            return true;
        }

        public static bool operator !=(SystemOfLinearEquation a, SystemOfLinearEquation b)
        {
            if (a == b)
                return false;
            else 
                return true;
        }

        private void swap(LinearEquation a,LinearEquation b)
        {
            LinearEquation temp = new LinearEquation(a);
            b.giveField(a);
            temp.giveField(b);
        }

        public void ToSteppedView()
        {
            int equationForSwapIndex, notNullElementIndex;

            for (int i = 0; i < size; i++)
            {
                notNullElementIndex = i;

                //если дигональный элемент равен нулю
                if (this[i][notNullElementIndex] == 0)
                {
                    //ищем первый ненулевой элемент справа от диагонального
                    while (this[i][notNullElementIndex] == 0 && notNullElementIndex < n)
                        notNullElementIndex++;

                    equationForSwapIndex = 1;

                    //ищем первое следующее уравнение где позиция найденного не нулевого элемента равна нулю
                    while (i + equationForSwapIndex < size && this[i + equationForSwapIndex][notNullElementIndex] == 0)
                        equationForSwapIndex++;

                    //если вышли за пределы системы
                    if (i + equationForSwapIndex >= size-1)
                        return;
                    else
                        swap(this[i], this[i + equationForSwapIndex]);
                }

                //вычитание нашего уравнения из всех следующих уравнений чтобы были нули под диагональю
                for (int j = i + 1; j < size; j++)
                {
                    this[j] -= this[i] * (this[j][i] / this[i][i]);
                }
            }
        }

        public double[] solve()
        {
            //удаляем пустые уравнения
            while (this[size - 1].isEmptyEquation())
                this.system.RemoveAt(size - 1);

            if (this[size - 1])
                ;
            else
                throw new ArithmeticException();//has not solution

            if (size != n)
                throw new ArithmeticException();//any solving is solution

            double[] result = new double[n];

            for (int i = size - 1; i >= 0; i--)
            {
                //присваиваем решению коэффициент элемента который без переменной
                result[i] = this[i][n];

                //вычитаем все найденные корни умноженные на соответсвующие коэффициенты
                for (int j = i + 1; j < n; j++)
                {
                    result[i] -= this[i][j] * result[j];
                }

                //делим на коэффициент при вычисляемом корне
                result[i] /= this[i][i];
            }
            return result;
        }
    }
}
