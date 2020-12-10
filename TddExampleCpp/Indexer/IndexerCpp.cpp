#include "IndexerCpp.h"
#include<stdexcept>
#include<exception>


IndexerCpp::IndexerCpp(double* array, int arrayLength, int beginIndex, int indexerLength)
{
	if (CheckArguments(arrayLength, beginIndex, indexerLength)) {
		this->arr = array;
		this->begin = beginIndex;
		this->length = indexerLength;
	}
	else throw std::invalid_argument("not correct arguments");
}
double& IndexerCpp::operator[](int index)
{
	if (CheckIndex(begin, length, index))
		return arr[begin + index];
	else throw std::out_of_range("incorrect index");
}
bool IndexerCpp::CheckArguments(int arrayLength, int beginIndex, int indexerLength)
{
	if (beginIndex<0 || indexerLength <= 0 || beginIndex + indexerLength>arrayLength) return false;
	else return true;
}
bool IndexerCpp::CheckIndex(int begin, int length, int index)
{
	if (index<0 || index + begin>length) return false;
	else return true;
}