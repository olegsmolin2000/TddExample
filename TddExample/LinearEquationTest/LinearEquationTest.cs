using Microsoft.VisualStudio.TestTools.UnitTesting;
using GaussMethod;
using System.Collections.Generic;
using System;
using System.Linq;

namespace LinearEquationTest
{
    [TestClass]
    public class LinearEquationTest
    {
        [TestMethod]
        public void CorrectIndexing()
        {
            LinearEquation equation = new LinearEquation("1 2,2");
            Assert.AreEqual(2.2, equation[1]);
        }

        [TestMethod]
        [ExpectedException(typeof(IndexOutOfRangeException))]
        public void IncorrectIndexingSubZero()
        {
            LinearEquation equation = new LinearEquation("1 2 3");
            Assert.AreEqual(typeof(IndexOutOfRangeException), equation[-1]);
        }

        [TestMethod]
        [ExpectedException(typeof(IndexOutOfRangeException))]
        public void IncorrectIndexingUnderCount()
        {
            LinearEquation equation = new LinearEquation("1 2 3");
            Assert.AreEqual(typeof(IndexOutOfRangeException), equation[4]);
        }

        [TestMethod]
        public void ConstructorByString()
        {
            LinearEquation equation = new LinearEquation("1 2 3 4 5,5");
            Assert.IsTrue(new double[] { 1, 2, 3, 4, 5.5 }.SequenceEqual((double[])equation));
        }

        [TestMethod]
        public void ConstructorByArray()
        {
            double[] array = new double[] { 1, 2, 3, 4, 5 }; 
            LinearEquation equation = new LinearEquation(array);
            Assert.IsTrue(new double[] { 1, 2, 3, 4, 5 }.SequenceEqual((double[])equation));
        }

        [TestMethod]
        public void ConstructorByList()
        {
            List<double> list = new List<double>() { 1, 2, 3, 4, 5 } ;
            LinearEquation equation = new LinearEquation(list);
            Assert.IsTrue(new double[] { 1, 2, 3, 4, 5 }.SequenceEqual((double[])equation));
        }

        [TestMethod]
        public void ConstructorByEmptyKoeffs()
        {
            LinearEquation equation = new LinearEquation(4);
            Assert.IsTrue(new double[] { 0, 0, 0, 0 }.SequenceEqual((double[])equation));
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void ConstructorByEmptyKoeffsIncrorrectArgument()
        {
            Assert.AreEqual(typeof(ArgumentException), new LinearEquation(-1));
        }

        [TestMethod]
        public void FillBySameValues()
        {
            LinearEquation equation = new LinearEquation(3);
            equation.SetSameValues(1.1);
            Assert.IsTrue(new double[] { 1.1 , 1.1 , 1.1 }.SequenceEqual((double[])equation));
        }

        [TestMethod]
        public void CorrectAdd()
        {
            LinearEquation equation1 = new LinearEquation("1 2 3");
            LinearEquation equation2 = new LinearEquation("0,5 2,1 1,1 11,2");
            Assert.IsTrue(new double[] { 1.5, 4.1, 4.1, 11.2 }.SequenceEqual((double[])(equation1 + equation2)));
        }

        [TestMethod]
        public void CorrectSubstract()
        {
            LinearEquation equation1 = new LinearEquation("1 2 3");
            LinearEquation equation2 = new LinearEquation("0,5 2 1,1 11,5");
            Assert.IsTrue(new double[] { 0.5, 0, 1.9, -11.5 }.SequenceEqual((double[])(equation1 - equation2)));
        }

        [TestMethod]
        public void MultyplyLeft()
        {
            LinearEquation equation = new LinearEquation("1 2 3");
            Assert.IsTrue(new double[] { 3, 6, 9 }.SequenceEqual((double[])(equation * 3)));
        }

        [TestMethod]
        public void MultyplyRight()
        {
            LinearEquation equation = new LinearEquation("1 2 3");
            Assert.IsTrue(new double[] { 3, 6, 9 }.SequenceEqual((double[])(3 * equation)));
        }

        [TestMethod]
        public void UnaryMinus()
        {
            LinearEquation equation = new LinearEquation("1 2 3");
            Assert.IsTrue(new double[] { -1, -2, -3 }.SequenceEqual((double[])( -equation)));
        }

        [TestMethod]
        public void EqualOperator()
        {
            LinearEquation equation = new LinearEquation("1 2 3");
            Assert.IsTrue(equation == (new LinearEquation("1 2 3")));
        }

        [TestMethod]
        public void NotEqualOperator()
        {
            LinearEquation equation = new LinearEquation("1 2 33");
            Assert.IsTrue(equation != (new LinearEquation("1 2 3")));
        }

        [TestMethod]
        public void CanBeSolved()
        {
            LinearEquation equation = new LinearEquation("1 2 33");
            Assert.IsTrue(equation?true:false);
        }

        [TestMethod]
        public void CanNotBeSolved()
        {
            LinearEquation equation = new LinearEquation("0 0 33");
            Assert.IsTrue(equation?false:true);
        }

        [TestMethod]
        public void CorrectString()
        {
            string str = "-1,1 2 2";
            LinearEquation equation = new LinearEquation(str);
            Assert.AreEqual(str, equation.ToString());
        }

    }
}
