#include "pch.h"
#include "CppUnitTest.h"

#include"../GaussMethod/SystemLinearEquation.h"
#include"../GaussMethod/SystemLinearEquation.cpp"
#include"../GaussMethod/LinearEquation.h"
#include"../GaussMethod/LinearEquation.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemLinearEquationTest
{
	TEST_CLASS(SystemLinearEquationTest)
	{
	public:
		
		TEST_METHOD(CorrectIndex)
		{
			SystemLinearEquation s(3);
			s.add(LinearEquation("1 2 3 5"));
			s.add(LinearEquation("2 3 4 7"));
			Assert::AreEqual(3.0, s[1][1]);
		}
		TEST_METHOD(CorrectSolution)
		{
			int n = 3;
			SystemLinearEquation s(n);
			LinearEquation a1("3.0 2.0 -4.0 3.0");
			LinearEquation a2("2.0 3.0 3.0 15.0");
			LinearEquation a3("5.0 -3 1.0 14.0");
			s.add(a1);
			s.add(a2);
			s.add(a3);
			s.steppingUp();
			vector<double> solve1 = s.solveSystem();
			bool check = true;
			vector<double>solve2{ 3,1,2 };
			for (int i = 0; i < solve1.size(); i++)
				if (abs(solve1[i] - solve2[i]) > 1e-9) check = false;
			Assert::AreEqual(true, check);
		}

		TEST_METHOD(HasNoSolution)
		{
			auto func = []()
			{
				int n = 3;
				SystemLinearEquation s(n);
				LinearEquation a1("3.0 2.0 -4.0 3.0");
				LinearEquation a2("6.0 4.0 -8.0 15.0");
				LinearEquation a3("6.0 4.0 -8.0 15.0");
				s.add(a1);
				s.add(a2);
				s.add(a3);
				s.steppingUp();
				vector<double> solve1 = s.solveSystem();
			};
			Assert::ExpectException< std::invalid_argument>(func);
		}

		TEST_METHOD(AnySolution)
		{
			auto func = []()
			{
				int n = 3;
				SystemLinearEquation s(n);
				LinearEquation a1("1 2 3 15");
				LinearEquation a2("6.0 4.0 -8.0 15.0");
				LinearEquation a3("6.0 4.0 -8.0 15.0");
				s.add(a1);
				s.add(a2);
				s.add(a3);
				s.steppingUp();
				vector<double> solve1 = s.solveSystem();
			};
			Assert::ExpectException< std::invalid_argument>(func);
		}
		TEST_METHOD(FailWithIndexing1)
		{
			auto func = []() {
				SystemLinearEquation s(3);
				s.add(LinearEquation("1 2 3 3"));
				LinearEquation tmp = s[-1]; };
			Assert::ExpectException<std::out_of_range>(func);
		}
		TEST_METHOD(FailWithIndexing2)
		{
			auto func = []() {
				SystemLinearEquation s(3);
				s.add(LinearEquation("1 2 3 3"));
				LinearEquation tmp = s[15]; };
			Assert::ExpectException<std::out_of_range>(func);
		}

		TEST_METHOD(FailWithAddEquation)
		{
			auto func = []() {SystemLinearEquation s(3);
			s.add(LinearEquation("1 2 3 3 4 6 7 8 5")); };
			Assert::ExpectException<std::invalid_argument>(func);
		}
	};
}
