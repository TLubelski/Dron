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
    void calculateVertexArr(double x_dim, double y_dim, double z_dim);

public:
    Cuboid() = delete;

    Cuboid(std::shared_ptr<drawNS::Draw3DAPI> _api, Vector3D _center, double x_dim, double y_dim, double z_dim, std::string color = "black")
    : Solid(_api, _center)
    {
        this->color = color;
        calculateVertexArr(x_dim, y_dim, z_dim);
    }

    virtual void draw() override;

    virtual void erase() override;

    virtual void redraw() override;

    virtual void rotate(const Rotation &r_matrix) override;

    void relocate(const Vector3D & shift);
};


#endif