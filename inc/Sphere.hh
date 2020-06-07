#ifndef SPHERE_HH
#define SPHERE_HH

/*!
 * \file Sphere.hh
 * File contains Sphere class definition
 */

#include "Solid.hh"

/****************************************
 \brief Class of Sphere geometry
*****************************************/
class Sphere : public Solid
{
protected:
    /*!
     * \brief Stores radius of sphere
     */
    double radius;

    /*!
     * \brief Stores upper assembly part of sphere
     */
    std::vector<std::vector<Vector3D>> assembly_up;
    
    /*!
     * \brief Stores lower assembly part of sphere
     */
    std::vector<std::vector<Vector3D>> assembly_down;

public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Sphere() = delete;

    /*!
     * \brief Full parametric constructor
     * \param _api shared pointer to gnuplot api
     * \param _center center point of figure
     * \param _radius radius of sphere
     * \param _color Color of figure
     */
    Sphere( std::shared_ptr<drawNS::Draw3DAPI>  _api, Vector3D _center, double _radius, std::string _color = "black" )
    : Solid(_api, _center, _color), radius(_radius)
    {
        calculateGeometry();
        draw();
    }

    /*!
     * \brief Calculates geometry of sphere
     */
    void calculateGeometry();

    /*!
     * \brief Drawing in scene
     */
    virtual void draw() override;

};


#endif