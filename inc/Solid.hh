#ifndef SOLID_HH
#define SOLID_HH

#include "Dr3D_gnuplot_api.hh"
#include "Rotation.hh"


/****************************************
 Class of Solid geometry object
*****************************************/
class Solid
{
protected:
    std::shared_ptr<drawNS::Draw3DAPI> api;
    uint id;
    Vector3D center;
    Rotation orientation;
    std::string color = "black";

    Solid(std::shared_ptr<drawNS::Draw3DAPI> _api, Vector3D _center)
        : api(_api), center(_center){}

public:
    Solid() = delete;
    virtual void draw() = 0;
    virtual void erase() = 0;
    virtual void redraw() = 0;
    virtual void rotate(const Rotation & r_matrix) = 0;
};


#endif