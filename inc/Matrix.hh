#ifndef MATRIX_HH
#define MATRIX_HH

/*!
 * \file Matrix.hh
 * File contains template for 3D Matrix class
 */

#include "size.hh"
#include "Vector.hh"

/*!
 * \brief Enum to choose det calculing method
 */
enum Det_method{ Gauss, Sarruss, Bareiss };

/*******************************
  \brief Square matrix class template
  \param TYPE type of stored data
  \param SIZE size of matrix
*******************************/
template<typename TYPE, int SIZE>
class Matrix
{
protected:
    /*!
     * \brief Stores array of vectors (row interpretation)
     */
    Vector<TYPE, SIZE> data[SIZE];

    /*!
     * \brief Return determinant using Gauss-Jordan method
     */
    TYPE det_gauss() const;

    /*!
     * \brief Return determinant using Bareiss method
     */
    TYPE det_bareiss() const;
    
    /*!
     * \brief Return determinant using Sarruss method (only for 3x3)
     */
    TYPE det_sarruss() const;

public:
    /*!
     * \brief Default constructor, set 0 in every cell
     */
    Matrix(){}

    /*!
     * \brief Initializer list constructor
     * \param list list for TYPE Vectors
     */
    Matrix(std::initializer_list<Vector<TYPE,SIZE>> list); 

    /*!
     * \brief Read operator[]
     * \param index index to access value
     */
    const Vector<TYPE, SIZE> & operator[](int index) const;

    /*!
     * \brief Write operator[]
     * \param index index to access value
     */
    Vector<TYPE, SIZE> & operator[](int index);

    /*!
     * \brief Camparison of 2 matrixes
     */
    bool operator==(const Matrix &M2) const;

    /*!
     * \brief Negated camparison of 2 matrixes
     */    
    bool operator!=(const Matrix &M2) const;

    /*!
     * \brief Return sum of this and M2
     */
    Matrix operator+(const Matrix &M2) const;

    /*!
     * \brief Add M2 to this
     */
    const Matrix & operator+=(const Matrix &M2);

    /*!
     * \brief Return difference of this and M2
     */
    Matrix operator-(const Matrix &M2) const;

    /*!
     * \brief Substract M2 from this
     */    
    const Matrix & operator-=(const Matrix &M2);

    /*!
     * \brief Return Multipling 2 matrixes (order matters)
     */  
    Matrix operator*(const Matrix &M2) const;
    
    /*!
     * \brief Return matrix multiplied by vector
     */  
    Vector<TYPE, SIZE> operator*(const Vector<TYPE, SIZE> &V2) const;

    /*!
     * \brief Return matrix multiplied by variable
     */  
    Matrix operator*(const TYPE &multi) const;  

    /*!
     * \brief Make this unit matrix
     */  
    void make_I();

    /*!
     * \brief Return stepped matrix
     */  
    Matrix stepped() const; 

    /*!
     * \brief Return transposed matrix
     */  
    Matrix transposition() const; 

    /*!
     * \brief Return determinant of matrix
     * \param method Select method to use (Gauss, Bareiss, Sarruss)
     */ 
    TYPE det(Det_method method = Bareiss) const;

    /*!
     * \brief Return inverted matrix
     */ 
    Matrix invert() const;
};


/*********************************
  \brief Matrix Output stream operator<<
**********************************/
template <typename TYPE, int SIZE>
std::ostream &operator<<(std::ostream &strm, const Matrix<TYPE,SIZE> &M); //wyswietlanie wierszami

/*********************************
  \brief Matrix Input stream operator>>
**********************************/
template <typename TYPE, int SIZE>
std::istream &operator>>(std::istream &strm, Matrix<TYPE,SIZE> &M); //wczytywanie wierszami

/*******************************************
 \brief Typedef of _SIZE_ matrix
********************************************/
typedef Matrix<double, _SIZE_> Matrix3D;

#endif