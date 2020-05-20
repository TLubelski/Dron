#include "Matrix.hh"
#include "cmp.hh"

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;


/********************
  List constructor 
********************/
template <typename TYPE, int SIZE>
Matrix<TYPE, SIZE>::Matrix(std::initializer_list<Vector<TYPE, SIZE>> list)
{
    if (list.size() != SIZE)
    {
        cerr << "[!]Incorrect number of arguments in Vector" << endl;
        exit(1);
    }

    int i = 0;
    for (auto arg : list)
        this->data[i++] = arg;
}

/**********************
  Read operator[]
**********************/
template <typename TYPE, int SIZE>
const Vector<TYPE, SIZE> & Matrix<TYPE, SIZE>::operator[](int index) const
{
    if (index < 0 || index >= SIZE)
    {
        cerr << "[!] Index out of range in Matrix" << endl;
        exit(1);
    }
    return data[index];
}

/**********************
  Write operator[]
**********************/
template <typename TYPE, int SIZE>
Vector<TYPE, SIZE> & Matrix<TYPE, SIZE>::operator[](int index)
{
    if (index < 0 || index >= SIZE)
    {
        cerr << "[!] Index out of range in Matrix" << endl;
        exit(1);
    }
    return data[index];
}

/**********************
  Logic operators
**********************/
template <typename TYPE, int SIZE>
bool Matrix<TYPE, SIZE>::operator==(const Matrix &M2) const
{
    bool wynik = true;
    for (int i = 0; i < SIZE; i++)
    {
        if (data[i] != M2.data[i])
            wynik = false;
    }
    return wynik;
}

template <typename TYPE, int SIZE>
bool Matrix<TYPE, SIZE>::operator!=(const Matrix &M2) const
{
    return !(*this == M2);
}

/**********************
  Adding operators
**********************/
template <typename TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::operator+(const Matrix &M2) const
{
    Matrix tmp;
    for (int i = 0; i < SIZE; i++)
        tmp.data[i] = data[i] + M2.data[i];
    return tmp;
}

template <typename TYPE, int SIZE>
const Matrix<TYPE, SIZE> &Matrix<TYPE, SIZE>::operator+=(const Matrix &M2)
{
    *this = *this + M2;
    return *this;
}

/**************************
  Subtraction operators
**************************/
template <typename TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::operator-(const Matrix &M2) const
{
    Matrix tmp;
    for (int i = 0; i < SIZE; i++)
        tmp.data[i] = data[i] - M2.data[i];
    return tmp;
}

template <typename TYPE, int SIZE>
const Matrix<TYPE, SIZE> &Matrix<TYPE, SIZE>::operator-=(const Matrix &M2)
{
    *this = *this - M2;
    return *this;
}

/*********************************
  Matrix multiplication operator
**********************************/
template <typename TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::operator*(const Matrix &M2) const
{
    Matrix tmp;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            tmp[i][j] = 0;
            for (int k = 0; k < SIZE; k++) //mnozenie wiersz x kolumny
                tmp[i][j] += data[i][k] * M2[k][j];
        }
    }
    return tmp;
}

/***************************************
  Matrix-Vector multiplication operator
****************************************/
template <typename TYPE, int SIZE>
Vector<TYPE, SIZE> Matrix<TYPE, SIZE>::operator*(const Vector<TYPE, SIZE> &W2) const
{
    Vector<TYPE, SIZE> tmp;
    for (int i = 0; i < SIZE; i++)
    {
        tmp[i] = data[i] * W2;
    }
    return tmp;
}

/***************************************
  Matrix-TYPE multiplication operator
****************************************/
template <typename TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::operator*(const TYPE & multi) const //mnozenie przez liczbe
{
    Matrix tmp;
    for (int i = 0; i < SIZE; i++)
        tmp[i] = data[i] * multi;
    return tmp;
}

/*********************************
  Make matrix a unit matrix
**********************************/
template <typename TYPE, int SIZE>
void Matrix<TYPE, SIZE>::make_I()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            data[i][j] = (i == j) ? 1 : 0;
        }
    }
}

/*********************************
  Return stepped matrix
**********************************/
template <typename TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::stepped() const
{
    Matrix tmp = *this;
    TYPE multiplier;
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = i + 1; j < SIZE; j++)
        {
            if( cmp(tmp[i][i], 0) )
            {
                cerr << "[!]Dividing by 0" << endl;
                exit(1);
            }
            multiplier = (-1) * tmp[j][i] / tmp[i][i]; //obliczanie mnoznika  wiersza
            tmp[j] += tmp[i] * multiplier;  //dodwawanie pomnozonego wiersza by uzyskac 0
        }
    }
    return tmp;

}

/*********************************
  Return transposed matrix
**********************************/
template <typename TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::transposition() const
{
    Matrix tmp;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            tmp[i][j] = data[j][i]; //zamina wierszy z kolumnami
        }
    }
    return tmp;
}

/*********************************
  Return det of matrix
**********************************/
template <typename TYPE, int SIZE>
TYPE Matrix<TYPE, SIZE>::det(Det_method method) const
{
    TYPE det;
    det = 0;
    
    if( SIZE == 2) //macierz 2x2 na krzyz
    {
        det = data[0][0] * data[1][1] - data[0][1] * data[1][0];  
    }
    else if(SIZE >= 3) // macierz 3x3 i wieksza
    {
        switch ( method )
        {
        case Bareiss:
            det = this->det_bareiss();
            break;
        
        case Gauss:
            det = this->det_gauss();
            break;

        case Sarruss:
            if(SIZE != 3)
            {
                cerr << "[!] Incorrect method in DET" << endl;
                exit(1);
            }
            det = this->det_sarruss();
            break;
        }
    }

    if (cmp(det, 0) ) //zabezpieczenie przed wynikiem -0
        det = 0;

    return det;
}

/*********************************
  Return inverted matrix
**********************************/
template <typename TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::invert() const
{
    Matrix tmp = *this;
    Matrix attached;
    attached.make_I();
    TYPE multiplier;

    if( cmp(tmp.det(), 0) )
    {
        cerr << "[!]Det = 0, matrix non-invertable" << endl;
        exit(1);
    }

    //do schodkowej
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = i + 1; j < SIZE; j++)
        {
            if ( cmp(tmp[i][i], 0) )
            {
                bool zero = true;
                for(int k = i+1; k < SIZE && zero; k++)
                {
                    swap(tmp[i], tmp[k]);
                    swap(attached[i], attached[k]);
                    if( !cmp(tmp[i][i], 0) )
                        zero = false;
                }
                if( cmp(tmp[i][i], 0) )
                {
                    cerr << "[!]Dividing by 0" << endl;
                    exit(1);
                }
            }
            multiplier = (-1) * tmp[j][i] / tmp[i][i]; //obliczanie mnoznika  wiersza
            tmp[j] += tmp[i] * multiplier;       //dodwawanie pomnozonego wiersza by uzyskac 0
            attached[j] += attached[i] * multiplier;
        }
    }

    //do diagonalnej
    for (int i = SIZE - 1; i > 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if ( cmp(tmp[i][i], 0) )
            {
                cerr << "[!]Dividing by 0" << endl;
                exit(1);
            }
            multiplier = (-1) * tmp[j][i] / tmp[i][i]; //obliczanie mnoznika  wiersza
            tmp[j] += tmp[i] * multiplier;  //dodwawanie pomnozonego wiersza by uzyskac 0
            attached[j] += attached[i] * multiplier;
        }
    }

    //do jednostkowej
    for(int i = 0; i < SIZE; i++)
    {
        attached[i] =  attached[i] / tmp[i][i];
    }

    return attached;
}

/*********************************
  Det internal method: Gauss
**********************************/
template <typename TYPE, int SIZE>
TYPE Matrix<TYPE, SIZE>::det_gauss() const
{
    TYPE det;
    det = 1;
    Matrix tmp = this->stepped();

    for (int i = 0; i < SIZE; i++) //mnozenie po glownej przekatnej
        det *= tmp[i][i];

    return det;
}

/*********************************
  Det internal method: Bareiss
**********************************/
template <typename TYPE, int SIZE>
TYPE Matrix<TYPE, SIZE>::det_bareiss() const
{
    Matrix tmp = *this;

    for (int i = 0; i < SIZE - 1; i++)
        for (int j = i + 1; j < SIZE; j++)
            for (int k = i + 1; k < SIZE; k++)
            {
                tmp[j][k] = (tmp[j][k] * tmp[i][i] - tmp[j][i] * tmp[i][k]);
                if (i)
                {
                    if( cmp(tmp[i-1][i-1], 0) )
                    {
                        cerr << "[!]Dividing by 0" << endl;
                        exit(1);
                    }
                    tmp[j][k] /= tmp[i - 1][i - 1];
                }

            }

    return tmp[SIZE - 1][SIZE - 1];
}

/*********************************
  Det internal method: Sarruss
**********************************/
template <typename TYPE, int SIZE>
TYPE Matrix<TYPE, SIZE>::det_sarruss() const
{
    TYPE det;
    det = (data[0][0] * data[1][1] * data[2][2] + data[0][1] * data[1][2] * data[2][0] + data[0][2] * data[1][0] * data[2][1]);
    det -= (data[0][2] * data[1][1] * data[2][0] + data[0][0] * data[1][2] * data[2][1] + data[0][1] * data[1][0] * data[2][2]);
    return det;
}

/*********************************
  Output stream operator<<
**********************************/
template <typename TYPE, int SIZE>
std::ostream &operator<<(std::ostream &strm, const Matrix<TYPE, SIZE> &M)
{
    for(int i =0; i < SIZE; i++)
    {
        strm << M[i] << endl;
    }
    return strm;
}

/*********************************
  Input stream operator>>
**********************************/
template <typename TYPE, int SIZE>
std::istream &operator>>(std::istream &strm, Matrix<TYPE, SIZE> &M)
{
    for (int i = 0; i < SIZE; i++)
    {
        strm >> M[i];
    }
    return strm;
}

