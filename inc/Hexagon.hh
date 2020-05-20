#ifndef HEXAGON_HH
#define HEXAGON_HH

/*!
 * \file Hexagon.hh
 * File contains Hexagon class definition
 */

#include "Solid.hh"

/***********************
 \brief Class of Hexagon
************************/
class Hexagon : public Solid
{
protected:
    /*!
     * \brief Stores height
     */
    const double height;
    
    /*!
     * \brief Stores radius
     */
    const double radius;

    /*!
     * \brief Stores location of vertexes
     */
    std::vector<Vector3D> vertexArr;

    /*!
     * \brief Calculates location of every vertex
     */
    void calculateVertexArr();

public:
    /*!
     * \brief Full parametric constructor
     * \param api shared pointer to gnuplot api
     * \param center start point
     * \param _height Z dimension of figure
     * \param _radius XY dimension of figure
     * \param color Color of figure
     */
    Hexagon(std::shared_ptr<drawNS::Draw3DAPI> api, Vector3D center, double _height, double _radius, std::string color = "black")
        : Solid(api, center, color), height(_height), radius(_radius) 
            { vertexArr.reserve(12); } 

    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Hexagon() = delete;

    /*!
     * \brief Drawing vertexes into scene
     */
    virtual void draw() override;

};

#endif