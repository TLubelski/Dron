#ifndef SCREW_HH
#define SCREW_HH

#include "Cuboid.hh"


enum Side{side_L, side_R};

class Screw : public Cuboid
{
private:
    const Side side;
    const double d_dims[3];

    void mount()
    {
        center[1] -= (d_dims[1]/2.0 + dims[1]/2.0); //mount to back
            
        if( side == side_L ) //mount to left
                center[0] -= (d_dims[0]/2.0 - dims[2]/2.0);
            else //mount to right
                center[0] += (d_dims[0]/2.0 - dims[2]/2.0);
    }

public:
    Screw() = delete;

    Screw(std::shared_ptr<drawNS::Draw3DAPI> _api, Vector3D d_center, double d_dim_X, double d_dim_Y, double d_dim_Z, Side _side, std::string color = "black") 
        : Cuboid(_api, d_center, d_dim_Z/4.0, d_dim_Z, d_dim_Z, color), 
            side(_side), d_dims{d_dim_X, d_dim_Y, d_dim_Z}
        { 
            mount();
            draw();
        }    

    void animate_m(Vector3D shift)
    {
        rotate(Rotation(Y_axis, 20));
        relocate(shift);
        redraw();
    }

    void animate_t(Vector3D _center, Rotation _orientation, bool working)
    {
        if(working)
            rotate(Rotation(Y_axis, 20));

        center = _center;
        orientation = _orientation;
        mount();
        center = orientation * center;
        redraw();
    }

};


#endif