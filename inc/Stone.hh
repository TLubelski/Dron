#ifndef STONE_HH
#define STONE_HH

#include "Cuboid.hh"

/********************
 Just standing rock
*********************/
class Stone : public Cuboid
{
public:
    Stone(std::shared_ptr<drawNS::Draw3DAPI> _api, Vector3D _center, double x_dim, double y_dim, double z_dim, std::string color = "black")
        : Cuboid(_api, _center, x_dim, y_dim, z_dim, color){ }
};

#endif