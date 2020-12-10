using Microsoft.VisualStudio.TestTools.UnitTesting;
using GaussMethod;
using System;
using System.Linq;

namespace SystemLinearEquationTest
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void CorrectConstructor()
        {
            SystemOfLinearEquation system = new SystemOfLinearEquation(2);

            LinearEquation a = new LinearEquation("1 2 3");

            system.add(a);
            system.add(-a);

            Assert.IsTrue(-a==system[1]);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void AddIncorrectLinearEquation()
        {
            SystemOfLinearEquation system = new SystemOfLinearEquation(2);
            system.add(new LinearEquation("1 2"));
            Assert.AreEqual(typeof(ArgumentException), system[0] = new LinearEquation("1 2 3"));
        }

        [TestMethod]
        [ExpectedException(typeof(IndexOutOfRangeException))]
        public void IncorrectIndexOver()
        {
            LinearEquation equation = new LinearEquation("1 2 3");

            SystemOfLinearEquation system = new SystemOfLinearEquation(2);

            system.add(equation);
            system.add(equation);

            Assert.Equals(typeof(IndexOutOfRangeException), system[2]);
        }

        [TestMethod]
        [ExpectedException(typeof(IndexOutOfRangeException))]
        public void IncorrectIndexUnder()
        {
            LinearEquation equation = new LinearEquation("1 2 3");

            SystemOfLinearEquation system = new SystemOfLinearEquation(2);

            system.add(equation);
            system.add(equation);

            Assert.Equals(typeof(IndexOutOfRangeException), system[-1]);
        }

        [TestMethod]
        public void CorrectSetter()
        {
            SystemOfLinearEquation system = new SystemOfLinearEquation(2);

            LinearEquation a = new LinearEquation("1 2 3");

            system.add(a);
            system.add(-a);
            system.add(a);

            LinearEquation newLinearEquation = new LinearEquation("2 2 2");

            system[2] = newLinearEquation;

            Assert.IsTrue(system[2]==newLinearEquation);
        }

        [TestMethod]
        public void CorrectSteppedView()
        {
            SystemOfLinearEquation result = new SystemOfLinearEquation(2);
            result.add(new LinearEquation("2 0 -2"));
            result.add(new LinearEquation("1 4 1"));
            result.add(new LinearEquation("-2 5 3"));
            result.ToSteppedView();

            SystemOfLinearEquation solve = new SystemOfLinearEquation(2);
            solve.add(new LinearEquation("2 0 -2"));
            solve.add(new LinearEquation("0 4 2"));
            solve.add(new LinearEquation("0 0 -1,5"));
            
            Assert.IsTrue(result == solve);
        }

        [TestMethod]
        public void CorrectEqual()
        {
            SystemOfLinearEquation a = new SystemOfLinearEquation(2);
            SystemOfLinearEquation b = new SystemOfLinearEquation(2);

            LinearEquation equation = new LinearEquation("1 2 2");

            a.add(equation);
            b.add(equation);

            a.add(-equation);
            b.add(-equation);

            Assert.IsTrue(a == b);
        }

        [TestMethod]
        public void CorrectNotEqual()
        {
            SystemOfLinearEquation a = new SystemOfLinearEquation(2);
            SystemOfLinearEquation b = new SystemOfLinearEquation(2);

            LinearEquation equation = new LinearEquation("1 2 2");

            a.add(equation);
            b.add(equation);

            a.add(-equation);
            b.add(equation);

            Assert.IsTrue(a != b);
        }

        [TestMethod]
        public void CorrectSolving()
        {
            SystemOfLinearEquation result = new SystemOfLinearEquation(3);
            result.add(new LinearEquation("1 1 2 2"));
            result.add(new LinearEquation("2 1 4 2"));
            result.add(new LinearEquation("1 2 0 2"));
            result.ToSteppedView();
            Assert.IsTrue(result.solve().SequenceEqual(new double[] { -2, 2, 1 }));
        }

        [TestMethod]
        [ExpectedException(typeof(ArithmeticException))]
        public void SystemHasNoSolution()
        {
            SystemOfLinearEquation result = new SystemOfLinearEquation(3);
            result.add(new LinearEquation("3 2 -4 3"));
            result.add(new LinearEquation("6 4 -8 15"));
            result.add(new LinearEquation("6 4 -8 15"));
            result.ToSteppedView();
            Assert.Equals(typeof(ArithmeticException), result.solve());
        }

        [TestMethod]
        [ExpectedException(typeof(ArithmeticException))]
        public void AnyValueIsSolution()
        {
            int n = 3;
            SystemOfLinearEquation result = new SystemOfLinearEquation(n);
            result.add(new LinearEquation("3 2 -4 7,5"));
            result.add(new LinearEquation("6 4 -8 15"));
            result.add(new LinearEquation("6 4 -8 15"));
            result.ToSteppedView();
            Assert.Equals(typeof(ArithmeticException), result.solve());
        }
    }
}
