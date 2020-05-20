#ifndef STONE_HH
#define STONE_HH

/*!
 * \file Stone.hh
 * File contains Stone class definition
 */

#include "Cuboid.hh"

/**************************
 \brief Just standing rock
**************************/
class Stone : public Cuboid
{
public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Stone() = delete;

    /*!
     * \brief Full parametric constructor
     * \param _api shared pointer to gnuplot api
     * \param _center point to spawn stone
     * \param x_dim X dimension of stone
     * \param y_dim Y dimension of stone
     * \param z_dim Z dimension of stone
     */
    Stone(std::shared_ptr<drawNS::Draw3DAPI> _api, Vector3D _center, double x_dim, double y_dim, double z_dim)
        : Cuboid(_api, _center, x_dim, y_dim, z_dim, "grey"){ }
};

#endif