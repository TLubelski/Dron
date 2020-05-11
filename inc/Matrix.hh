#ifndef MATRIX_HH
#define MATRIX_HH

#include "size.hh"
#include "Vector.hh"

enum Det_method{ Gauss, Sarruss, Bareiss };

/**************************
  Matrix class template
***************************/
template<typename TYPE, int SIZE>
class Matrix
{
protected:
    Vector<TYPE, SIZE> data[SIZE]; //kazdemu wierszowi odpowiada wektor

    /*METODY WEWNETRZNE*/
    TYPE det_gauss() const;
    TYPE det_bareiss() const;
    TYPE det_sarruss() const;

public:
    /*KONSTRUKTORY*/
    Matrix(){}
    Matrix(std::initializer_list<Vector<TYPE,SIZE>> list); //przyjmuje tablice wektorow

    /*OPERATORY*/
    const Vector<TYPE, SIZE> & operator[](int index) const;
    Vector<TYPE, SIZE> & operator[](int index);

    bool operator==(const Matrix &M2) const;
    bool operator!=(const Matrix &M2) const;

    Matrix operator+(const Matrix &M2) const;
    const Matrix & operator+=(const Matrix &M2);

    Matrix operator-(const Matrix &M2) const;
    const Matrix & operator-=(const Matrix &M2);

    Matrix operator*(const Matrix &M2) const; //mnozenie dwoch macierzy
    
    Vector<TYPE, SIZE> operator*(const Vector<TYPE, SIZE> &V2) const; //mnozenie przez wektor
    Matrix operator*(const TYPE &multi) const;                        // liczba

    /*API*/
    void make_I(); //tworzy macierz jednostkowa

    Matrix stepped() const; //zwraca macierz schodkowa

    Matrix transposition() const; 

    TYPE det(Det_method method = Bareiss) const;

    Matrix invert() const; //WIP
};


/*********************************
  Output stream operator<<
**********************************/
template <typename TYPE, int SIZE>
std::ostream &operator<<(std::ostream &strm, const Matrix<TYPE,SIZE> &M); //wyswietlanie wierszami

/*********************************
  Input stream operator>>
**********************************/
template <typename TYPE, int SIZE>
std::istream &operator>>(std::istream &strm, Matrix<TYPE,SIZE> &M); //wczytywanie wierszami

/*******************************************
 Typedef of _SIZE_ matrix
********************************************/
typedef Matrix<double, _SIZE_> Matrix3D;

#endif