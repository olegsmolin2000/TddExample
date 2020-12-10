using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.CompilerServices;
using System.Text;
using System.Text.RegularExpressions;

namespace GaussMethod
{
    public class LinearEquation
    {
        private List<double> koeffList;

        public LinearEquation(string koeffString)
        {
            string[] koeffs = koeffString.Split(' ');

            this.koeffList = new List<double>(koeffs.Length);

            foreach (var el in koeffs)
                this.koeffList.Add(double.Parse(el));
        }

        public LinearEquation(double[] array) {
            koeffList = new List<double>(array);
        }

        public LinearEquation(List<double> list)
        {
            koeffList = new List<double>(list);
        }

        public LinearEquation(int count)
        {
            if (count >= 0)
            {
                koeffList = new List<double>(count);

                for (int i = 0; i < count; i++)
                {
                    koeffList.Add(0);
                }
            }
            else
                throw new ArgumentException();
        }

        public void SetSameValues(double value)
        {
            for (int i = 0; i < koeffList.Count; i++)
            {
                koeffList[i] = value;
            }
        }

        public void SetRandomValues()
        {
            Random rand = new Random();

            for (int i = 0; i < koeffList.Count; i++)
            {
                koeffList[i] = (double)rand.Next(50) / 10;
            }
        }

        public static LinearEquation operator +(LinearEquation a,LinearEquation b)
        {
            double[] result = new double[Math.Max(a.koeffList.Count, b.koeffList.Count)];

            for (int i = 0; i < result.Length; i++)
            {
                result[i] = (i < a.koeffList.Count ? a[i] : 0) + (i < b.koeffList.Count ? b[i] : 0);
            }

            return new LinearEquation(result);
        }

        public static LinearEquation operator -(LinearEquation a, LinearEquation b)
        {
            double[] result = new double[Math.Max(a.koeffList.Count, b.koeffList.Count)];

            for (int i = 0; i < result.Length; i++)
            {
                result[i] = (i < a.koeffList.Count ? a[i] : 0) - (i < b.koeffList.Count ? b[i] : 0);
            }

            return new LinearEquation(result);
        }

        public static LinearEquation operator *(LinearEquation a,double r)
        {
            LinearEquation result = new LinearEquation(a);

            for (int i = 0; i < result.koeffList.Count; i++)
            {
                result.koeffList[i] *= r;
            }

            return result;
        }

        public static LinearEquation operator *(double r, LinearEquation a)
        {
            return a * r;
        }

        public static LinearEquation operator -(LinearEquation a)
        {
            LinearEquation result = new LinearEquation(a);

            for (int i = 0; i < result.koeffList.Count; i++)
            {
                result.koeffList[i] = -result.koeffList[i];
            }

            return result;
        }

        public static bool operator ==(LinearEquation a,LinearEquation b)
        {
            if (a.koeffList.Count != b.koeffList.Count)
                return false;
            else
            {
                for (int i = 0; i < a.koeffList.Count; i++)
                {
                    if (a.koeffList[i] != b.koeffList[i])
                        return false;
                }
            }
            return true;
        }

        public static bool operator !=(LinearEquation a,LinearEquation b)
        {
            return !(a == b);
        }

        public static bool operator true(LinearEquation a)
        {
            for (int i = 0; i < a.koeffList.Count-1; i++)
            {
                if (a.koeffList[i] != 0)
                    return true;
            }
            return a.koeffList[a.koeffList.Count - 1] == 0;
        }

        public static bool operator false(LinearEquation a)
        {
            return a ? false : true;
        }

        public override string ToString()
        {
            string result="";

            for (int i = 0; i < this.koeffList.Count-1; i++)
            {
                result += this.koeffList[i].ToString();
                result += " ";
            }

            result += this.koeffList[this.koeffList.Count - 1];

            return result;
        }

        public double this[int index]
        {
            get
            {
                if (index >= 0 && index < koeffList.Count)
                    return koeffList[index];
                else
                    throw new IndexOutOfRangeException();
            }
            set
            {
                if (index >= 0 && index < koeffList.Count)
                    koeffList[index] = value;
                else
                    throw new IndexOutOfRangeException();
            }
        }

        public static implicit operator double[](LinearEquation equation)
        {
            return equation.koeffList.ToArray();
        }

        public void giveField(LinearEquation other)
        {
            other.koeffList = this.koeffList.ToList();
        }

        public int Size => koeffList.Count;

        public bool isEmptyEquation()
        {
            for (int i = 0; i < Size; i++)
            {
                if (koeffList[i] != 0)
                    return false;
            }
            return true;
        }
    }
}
