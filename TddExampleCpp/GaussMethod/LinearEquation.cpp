#include "LinearEquation.h"
#include<vector>
#include<string>
#include<stdexcept>
#include<exception>
#include<ctime>

LinearEquation::LinearEquation(string str) {
    std::vector<std::string> strVector;

    int pos = str.find(" ");
    while (pos != std::string::npos) {
        strVector.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
        pos = str.find(" ");
    }

    if (!str.empty()) 
        strVector.push_back(str);
    
        for (int i = 0; i < strVector.size(); i++) 
            this->koeffs.push_back(std::stod(strVector[i]));
}

LinearEquation::LinearEquation(double* arr,int size) {
    for (size_t i = 0; i < size; i++)
        this->koeffs.push_back(*(arr + i));
}

LinearEquation::LinearEquation(std::vector<double> vec) {
    for (size_t i = 0; i < vec.size(); i++)
    {
        this->koeffs.push_back(vec[i]);
    }
}

LinearEquation::LinearEquation(int size) {
    for (size_t i = 0; i < size; i++)
    {
        this->koeffs.push_back(0);
    }
}

LinearEquation::LinearEquation(const LinearEquation& other) {
    this->koeffs = std::vector<double>(other.koeffs);
}

LinearEquation& LinearEquation::operator=(const LinearEquation& other) {
    this->koeffs = std::vector<double>(other.koeffs);
    return *this;
}

double& LinearEquation::operator[](int index) {
    if (index >= 0 && index < this->koeffs.size())
        return this->koeffs.at(index);
    else
        throw std::out_of_range("");
}

void LinearEquation::FillRandomValues() {
    srand(time(NULL));

    for (size_t i = 0; i < this->size(); i++)
    {
        this->koeffs[i] = rand() / 5;
    }
}

void LinearEquation::FillSameValues(double value) {
    for (size_t i = 0; i < this->size(); i++)
        this->koeffs[i] = value;
}

LinearEquation LinearEquation::operator+(LinearEquation& other) {
    if (this->size() != other.size())
        throw std::invalid_argument("");
    else {
        std::vector<double> summ=this->koeffs;

        for (size_t i = 0; i < this->size(); i++)
        {
            summ[i] += other[i];
        }
        return LinearEquation(summ);
    }
}

LinearEquation LinearEquation::operator-(LinearEquation& other) {
    if (this->size() != other.size())
        throw std::invalid_argument("");
    else {
        std::vector<double> summ=this->koeffs;

        for (size_t i = 0; i < this->size(); i++)
        {
            summ[i] -= other[i];
        }
        return LinearEquation(summ);
    }
}

LinearEquation LinearEquation::operator*(const double& value) {
    std::vector<double> result=this->koeffs;

    for (size_t i = 0; i < this->size(); i++)
    {
        result[i] *= value;
    }

    return LinearEquation(result);
}

LinearEquation operator*( double value,LinearEquation& LE) {
    return LE * value;
}

LinearEquation LinearEquation::operator-() {
    std::vector<double> result=this->koeffs;

    for (size_t i = 0; i < this->size(); i++)
    {
        result[i] = -result[i];
    }

    return LinearEquation(result);
}

LinearEquation::operator std::string(){
    std::string result = "";

    for (size_t i = 0; i < this->size()-1; i++)
    {
        result += std::to_string(this[i])+" ";
    }
    result += std::to_string(this[this->size() - 1]);

    return result;
}

LinearEquation::operator std::vector<double>() {
    std::vector<double> result=std::vector<double>(this->koeffs);

    return result;
}

LinearEquation::operator bool(){
    for (size_t i = 0; i < this->size()-1; i++)
    {
        if (this->koeffs[i] != 0)
            return true;
    }

    return (this->koeffs[this->size() - 1] == 0) ? true : false;
}

bool LinearEquation::operator==(const LinearEquation& other) {
    for (int i = 0; i < this->size(); i++)
        if (abs(this->koeffs[i] - other.koeffs[i]) > 1e-9)
            return false;
    return true;
}

bool LinearEquation::operator!=(const LinearEquation& other) {
    return !(*this == other);
}

bool LinearEquation::isNull() {
    for (int i = 0; i < size(); i++)
        if (this->koeffs[i] != 0)
            return false;
    return true;
}