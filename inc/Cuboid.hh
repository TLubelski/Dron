#ifndef CUBOID_HH
#define CUBOID_HH

#include "Solid.hh"


/********************
 Class of cuboid 
*********************/
class Cuboid : public Solid
{
protected:
    Vector3D vertexArr[8];
    const double dims[3];

    void calculateVertexArr();

    Cuboid(std::shared_ptr<drawNS::Draw3DAPI> _api, Vector3D _center, double x_dim, double y_dim, double z_dim, std::string color = "black")
        : Solid(_api, _center, color), dims{x_dim, y_dim, z_dim} { } 

public:
    Cuboid() = delete;

    virtual void draw() override;

    virtual void erase() override;

    virtual void redraw() override;
};


#endif