#ifndef SOLID_HH
#define SOLID_HH

#include "Drawable.hh"
#include "Rotation.hh"


/****************************************
 Class of Solid geometry object
*****************************************/
class Solid : public Drawable
{
protected:
    Vector3D center;
    Rotation orientation;

    Solid(std::shared_ptr<drawNS::Draw3DAPI> api, Vector3D _center, std::string color = "black")
        : Drawable(api, color), center(_center) { }

public:
    Solid() = delete;
    
    /***Standard methods***/
    void rotate(const Rotation &r_matrix)
        { orientation = orientation * r_matrix; }

    void relocate(const Vector3D &shift)
        { center += orientation * shift; }
};


#endif