#ifndef SOLID_HH
#define SOLID_HH

/*!
 * \file Solid.hh
 * File contains Solid class definition
 */

#include "Drawable.hh"
#include "Rotation.hh"

/****************************************
 \brief Class of Solid geometry object
*****************************************/
class Solid : public Drawable
{
protected:
    /*!
     * \brief Stores center point of figure
     */
    Vector3D center;

    /*!
     * \brief Stores orientation matrix of figure
     */
    Rotation orientation;

    /*!
     * \brief Full parametric constructor
     * \param _api shared pointer to gnuplot api
     * \param _center center point of figure
     * \param color Color of figure
     */
    Solid(std::shared_ptr<drawNS::Draw3DAPI> api, Vector3D _center, std::string color = "black")
        : Drawable(api, color), center(_center) 
        { }
        
public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Solid() = delete;
    
    /*!
     * \brief Rotates figure by angle
     * \param rmatrix Rotation matrix
     */
    void rotate(const Rotation &r_matrix)
        { orientation = orientation * r_matrix; }

    /*!
     * \brief Shifts object by Vector3D
     * \param shift shift Vector3D
     */
    void relocate(const Vector3D &shift)
        { center += orientation * shift; }
};


#endif