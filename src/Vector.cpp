#include "Vector.hh"
#include "cmp.hh"

#include <cmath>
#include <regex>
#include <sstream>

using namespace std;

/**********************
  Default constructor 
**********************/
template <typename TYPE, int SIZE>
Vector<TYPE, SIZE>::Vector()
{
    for (int i = 0; i < SIZE; i++)
        data[i] = 0;
}

/********************
  Array constructor 
********************/
template <typename TYPE, int SIZE>
Vector<TYPE, SIZE>::Vector(TYPE *data)
{
    for (int i = 0; i < SIZE; i++)
        this->data[i] = data[i];
}

/**********************
  Read operator[]
**********************/
template <typename TYPE, int SIZE>
const TYPE & Vector<TYPE, SIZE>::operator[](int index) const
{
    if (index < 0 || index >= SIZE)
    {
        cerr << "[!] Index out of range in Vector" << endl;
        exit(1);
    }
    return data[index];
}

/**********************
  Write operator[]
**********************/
template <typename TYPE, int SIZE>
TYPE & Vector<TYPE, SIZE>::operator[](int index)
{
    if (index < 0 || index >= SIZE)
    {
        cerr << "[!] Index out of range in Vector" << endl;
        exit(1);
    }
    return data[index];
}

/**********************
  Logic operators
**********************/
template <typename TYPE, int SIZE>
bool Vector<TYPE, SIZE>::operator==(const Vector &W2) const
{
    bool result = true;
    for (int i = 0; i < SIZE; i++)
    {
        if ( !cmp(data[i], W2.data[i]) )
            result = false;
    }
    return result;
}

template <typename TYPE, int SIZE>
bool Vector<TYPE, SIZE>::operator!=(const Vector &W2) const
{
    return !(*this == W2);
}

/**********************
  Adding operators
**********************/
template <typename TYPE, int SIZE>
Vector<TYPE,SIZE> Vector<TYPE, SIZE>::operator+(const Vector &W2) const
{
    Vector tmp;
    
    for (int i = 0; i < SIZE; i++)
        tmp.data[i] = data[i] + W2.data[i];
    
    return tmp;
}

template <typename TYPE, int SIZE>
const Vector<TYPE, SIZE> & Vector<TYPE, SIZE>::operator+=(const Vector &W2)
{
    *this = *this + W2;
    return *this;
}

/**************************
  Subtraction operators
**************************/
template <typename TYPE, int SIZE>
Vector<TYPE, SIZE> Vector<TYPE, SIZE>::operator-(const Vector &W2) const
{
    Vector tmp;
    
    for (int i = 0; i < SIZE; i++)
        tmp.data[i] = data[i] - W2.data[i];
    
    return tmp;
}

template <typename TYPE, int SIZE>
const Vector<TYPE, SIZE> & Vector<TYPE, SIZE>::operator-=(const Vector &W2)
{
    *this = *this - W2;
    return *this;
}

/*********************************
  Scalar multiplication operator
**********************************/
template <typename TYPE, int SIZE>
TYPE Vector<TYPE, SIZE>::operator*(const Vector &W2) const
{
    TYPE tmp;

    for (int i = 0; i < SIZE; i++)
        tmp += data[i] * W2.data[i];
    
    return tmp; 
}

/*********************************
  By variable dividing operator
**********************************/
template <typename TYPE, int SIZE>
Vector<TYPE, SIZE> Vector<TYPE, SIZE>::operator/(TYPE divider) const 
{
    Vector tmp;
    
    for (int i = 0; i < SIZE; i++)
        tmp[i] = data[i] / divider;
    
    return tmp;
}

/*********************************
  By variable multiplier operator
**********************************/
template <typename TYPE, int SIZE>
Vector<TYPE, SIZE> Vector<TYPE, SIZE>::operator*(const TYPE & multi) const
{
    Vector tmp;
    
    for (int i = 0; i < SIZE; i++)
        tmp[i] = data[i] * multi;
    
    return tmp;
}

/*********************************
  Vector length calculation method
**********************************/
template <typename TYPE, int SIZE>
double Vector<TYPE, SIZE>::length() const
{
    double sum;
    sum = 0;
    
    for (int i = 0; i < SIZE; i++)
        sum += data[i] * data[i];
    
    return sqrt(sum);
}

/*********************************
  Output stream operator<<
**********************************/
template <typename TYPE, int SIZE>
ostream & operator<<(ostream &strm, const Vector<TYPE,SIZE> &V)
{
    strm << "|";
    for(int i = 0; i < SIZE-1; i++)
        strm << V[i] << " ";
    
    strm << V[SIZE-1];
    strm << "|";    

    return strm;
}

/*********************************
  Input stream operator>>
**********************************/
template <typename TYPE, int SIZE>
istream & operator>>(istream &strm, Vector<TYPE,SIZE> &V)
{
    string pattern_regex = "\\|";
    string pattern_num = "\\-?\\d+.?\\d*";

    //building regex pattrern
    for (int i = 0; i < SIZE - 1; i++)
    {
        pattern_regex += pattern_num;
        pattern_regex += "\\s";
    }
    pattern_regex += pattern_num;
    pattern_regex += "\\|";
    regex pattern_final(pattern_regex); //regex init

    //read from stream
    stringstream ss;
    string input;
    smatch result;
    getline(strm, input);
    ss << input;

    char trash;
    if (regex_search(input, result, pattern_final)) //read data if match
    {
        ss >> trash;
        for (int i = 0; i < SIZE; i++)
            ss >> V[i];
    }
    else //print error
    {
        cerr << "[!] Incorrect input in Vector" << endl;
        exit(1); //or strm.setstate(ios::failbit);
    }

    return strm;
}
