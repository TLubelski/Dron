#ifndef VECTOR_HH
#define VECTOR_HH

/*!
 * \file Vector.hh
 * File contains template for 3D vector class
 */

#include "size.hh"

#include <iostream>

/*******************************
  \brief Vector class template
  \param TYPE type of stored data
  \param SIZE size of vector
*******************************/
template <typename TYPE, int SIZE>
class Vector
{
protected:
    /*!
     * \brief Stores vector's data as array
     */
    TYPE data[SIZE];

    /*!
     * \brief Stores total quantity of created Vectors
     */
    static inline unsigned int created = 0;
    
    /*!
     * \brief Stores quantity of Vectors on scene
     */
    static inline unsigned int existing = 0;

public:
    /*!
     * \brief Default constructor set (0,0,0)
     */
    Vector();

    /*!
     * \brief Initializer list constructor
     * \param list list for TYPE parameters
     */
    Vector(std::initializer_list <TYPE> list);

    /*!
     * \brief Copy constructor
     */
    Vector(const Vector & arg);

    /*!
     * \brief Default destructor
     */
    ~Vector(){ existing--; }

    /*!
     * \brief Getter of total created Vectors
     */
    static int getCreated(){ return created; }
    
    /*!
     * \brief Getter of total existing vectors
     */
    static int getExisting(){ return existing; }

    /*!
     * \brief Read operator[]
     * \param index index to access value
     */
    const TYPE &operator[](int index) const;
    
    /*!
     * \brief Write operator[]
     * \param index index to access value
     */
    TYPE &operator[](int index);
    
    /*!
     * \brief Camparison of 2 vectors
     */
    bool operator==(const Vector &V2) const;

    /*!
     * \brief Negated camparison of 2 vectors
     */
    bool operator!=(const Vector &V2) const;

    /*!
     * \brief Return sum of this and V2
     */
    Vector operator+(const Vector &V2) const;
    
    /*!
     * \brief Add v2 to this
     */
    const Vector & operator+=(const Vector &V2);

    /*!
     * \brief Return difference of this and V2
     */
    Vector operator-(const Vector &V2) const;
    
    /*!
     * \brief Substract V2 from this
     */
    const Vector & operator-=(const Vector &V2);

    /*!
     * \brief Return scalar product of this and V2
     */
    TYPE operator*(const Vector &V2) const; 

    /*!
     * \brief Return this multiplied by variable
     */
    Vector operator*(const TYPE & multi) const;

    /*!
     * \brief Return this divided by variable
     */
    Vector operator/(TYPE divider) const;

    /*!
     * \brief Return length of vector
     */
    double length() const;

};


/*****************************************
  \brief Vector output stream operator<<
*****************************************/
template <typename TYPE, int SIZE>
std::ostream &operator<<(std::ostream &strm, const Vector<TYPE, SIZE> &V);

/****************************************
  \brief Vector input stream operator>>
****************************************/
template <typename TYPE, int SIZE>
std::istream &operator>>(std::istream &strm, Vector<TYPE, SIZE> &V);


/*******************************************
 \brief Typedef of 3D vector
********************************************/
typedef Vector<double, _SIZE_> Vector3D;


#endif