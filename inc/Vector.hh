#ifndef VECTOR_HH
#define VECTOR_HH

#include "size.hh"
//#include "Dr3D_gnuplot_api.hh"
#include <iostream>


/**************************
  Vector class template
***************************/
template <typename TYPE, int SIZE>
class Vector
{
protected:
    TYPE data[SIZE];

public:
    /*CONSTRUCTORS*/
    Vector();
    Vector(std::initializer_list <TYPE> list);

    /*OPERATORS*/
    const TYPE &operator[](int index) const;
    TYPE &operator[](int index);
    
    bool operator==(const Vector &V2) const;
    bool operator!=(const Vector &V2) const;

    Vector operator+(const Vector &V2) const;
    const Vector & operator+=(const Vector &V2);

    Vector operator-(const Vector &V2) const;
    const Vector & operator-=(const Vector &V2);

    TYPE operator*(const Vector &V2) const; //scalar

    Vector operator*(const TYPE & multi) const; //by variable

    Vector operator/(TYPE divider) const; //by variable

    /*METHODS*/
    double length() const;

};


/*********************************
  Output stream operator<<
**********************************/
template <typename TYPE, int SIZE>
std::ostream &operator<<(std::ostream &strm, const Vector<TYPE, SIZE> &V);

/*********************************
  Input stream operator>>
**********************************/
template <typename TYPE, int SIZE>
std::istream &operator>>(std::istream &strm, Vector<TYPE, SIZE> &V);


/*******************************************
 Typedef of 3D vector
********************************************/
typedef Vector<double, _SIZE_> Vector3D;

#endif