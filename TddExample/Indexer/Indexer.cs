using System;
using System.Collections.Generic;
using System.Text;

namespace Indexer1
{
    public class Indexer
    {
        private double[] array;
        private int begin;
        private int length;

        public Indexer(double[] array, int begin, int length)
        {
            if (isCorrectArguments(array.Length, begin, length))
            {
                this.array = array;
                this.begin = begin;
                this.length = length;
            }
            else
                throw new ArgumentException();
        }

        public int Length { get => length; }

        public double this [int index]
        {
            get
            {
                if (isCorrectIndex(index))
                    return array[begin + index];
                else
                    throw new IndexOutOfRangeException();
            }
            set
            {
                if (isCorrectIndex(index))
                    array[begin + index] = value;
                else
                    throw new IndexOutOfRangeException();
            }
        }

        private bool isCorrectArguments(int arrayLength,int begin,int length)
        {
            return (begin >= 0 && length >= 0 && (begin + length) < arrayLength);
        }

        private bool isCorrectIndex(int index)
        {
            return (index >= 0 && index < length && index < begin + length);
        }
    }
}
