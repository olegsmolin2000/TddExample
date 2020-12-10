#include "pch.h"
#include "CppUnitTest.h"

#include "../Indexer/IndexerCpp.h"
#include "../Indexer/IndexerCpp.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IndexerTest
{
	TEST_CLASS(IndexerTest)
	{
	private:
		double* array = new double[5]{ 1,2,3,4,5 };

	public:
		
		TEST_METHOD(HaveCorrectLength)
		{
			IndexerCpp indexer(array, 5, 1, 2);
			Assert::AreEqual(2, indexer.getLength());
		}

		TEST_METHOD(GetCorrectly)
		{
			IndexerCpp indexer(array, 4, 1, 2);
			Assert::AreEqual(2.0, indexer[0]);
			Assert::AreEqual(3.0, indexer[1]);
		}

		TEST_METHOD(SetCorrectly)
		{
			IndexerCpp indexer(array, 4, 1, 2);
			indexer[0] = 10;
			Assert::AreEqual(10.0, array[1]);
		}

		TEST_METHOD(IndexerDoesNotCopyArray)
		{
			IndexerCpp indexer1(array, 4, 1, 2);
			IndexerCpp indexer2(array, 4, 0, 2);
			indexer1[0] = 12345;
			Assert::AreEqual(12345.0, indexer2[1]);
		}

		TEST_METHOD(FailWithWrongArguments1)
		{
			auto func = []() {
				double* arr = new double[4]{ 1, 2, 3, 4 };
				IndexerCpp temp(arr, 4, -1, 3);
			};
			Assert::ExpectException<std::invalid_argument>(func);
		}
		TEST_METHOD(FailWithWrongArguments2)
		{
			auto func = []() {
				double* arr = new double[4]{ 1, 2, 3, 4 };
				IndexerCpp temp(arr, 4, 1, -1);
			};
			Assert::ExpectException<std::invalid_argument>(func);
		}
		TEST_METHOD(FailWithWrongArguments3)
		{
			auto func = []() {
				double* arr = new double[4]{ 1, 2, 3, 4 };
				IndexerCpp temp(arr, 4, 1, 10);
			};
			Assert::ExpectException<std::invalid_argument>(func);
		}
		TEST_METHOD(FailWithWrongIndexing1)
		{
			auto func = []() {
				double* arr = new double[4]{ 1, 2, 3, 4 };
				IndexerCpp indexer(arr, 4, 1, 2);
				double temp = indexer[-1];
			};
			Assert::ExpectException<std::out_of_range>(func);
		}
		TEST_METHOD(FailWithWrongIndexing2)
		{
			auto func = []() {
				double* arr = new double[4]{ 1, 2, 3, 4 };
				IndexerCpp indexer(arr, 4, 1, 2);
				double tmp = indexer[10];
			};
			Assert::ExpectException<std::out_of_range>(func);
		}



	};
}
