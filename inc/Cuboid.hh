#ifndef CUBOID_HH
#define CUBOID_HH

/*!
 * \file Cuboid.hh
 * File contains cuboid class definition
 */

#include "Solid.hh"

/***********************
 \brief Class of cuboid 
************************/
class Cuboid : public Solid
{
protected:
    /*!
     * \brief Stores location of 8 vertexes
     */
    std::vector<Vector3D> vertexArr;
    
    /*!
     * \brief Stores dimensions of figure
     */
    const double dims[3];

    /*!
     * \brief Calculates location of every vertex
     */
    void calculateVertexArr();

    /*!
     * \brief Full parametric constructor
     * \param _api shared pointer to gnuplot api
     * \param x_dim X dimension of figure
     * \param y_dim Y dimension of figure
     * \param z_dim Z dimension of figure
     * \param color Color of figure
     */
    Cuboid(std::shared_ptr<drawNS::Draw3DAPI> _api, Vector3D _center, double x_dim, double y_dim, double z_dim, std::string color = "black")
        : Solid(_api, _center, color), dims{x_dim, y_dim, z_dim} 
            { vertexArr.reserve(8); } 

public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Cuboid() = delete;

    /*!
     * \brief Drawing vertexes into scene
     */
    virtual void draw() override;

};


#endif