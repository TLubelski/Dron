#ifndef SCREW_HH
#define SCREW_HH

#include "Cuboid.hh"


/*!
* \brief Enum to set side of screw
*/
enum Side{side_L, side_R};


/****************************
 \brief Class rotating screw
****************************/
class Screw : public Cuboid
{
private:
    const Side side;
    const double d_dims[3];
    Rotation screw_rot;

    /*!
     * \brief Calculates center point in reference to Drone size
     */
    void mount()
    {
        center[1] = -(d_dims[1]/2.0 + dims[1]/2.0); //mount to back
            
        if( side == side_L ) //mount to left
                center[0] = -(d_dims[0]/2.0 - dims[2]/2.0);
            else //mount to right
                center[0] = (d_dims[0]/2.0 - dims[2]/2.0);
    }

public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Screw() = delete;

    /*!
     * \brief Full parametric constructor
     * \param _api shared pointer to gnuplot api
     * \param d_center center point of drone
     * \param d_dim_X X dimension of Drone
     * \param d_dim_Y Y dimension of Drone
     * \param d_dim_Z Z dimension of Drone
     * \param _side Left or right side of drone's back
     * \param color Color of figure
     */
    Screw(std::shared_ptr<drawNS::Draw3DAPI> _api, Vector3D d_center, double d_dim_X, double d_dim_Y, double d_dim_Z, Side _side, std::string color = "black") 
        : Cuboid(_api, d_center, d_dim_Z/4.0, d_dim_Z, d_dim_Z, color), 
            side(_side), d_dims{d_dim_X, d_dim_Y, d_dim_Z}
        { 
            mount();
            draw();
        }    

    /*!
     * \brief Calculates screws for 1 frame
     * \param d_center Center point of Drone
     * \param d_rotation Rotation matrix of Drone
     * \param working Is now rotating
     */
    void animate(Vector3D d_center, Rotation d_rotation, bool working = true)
    {
        if( working )
            screw_rot = screw_rot  * Rotation(Y_axis, 20);

        orientation = screw_rot;

        rotate(d_rotation);

        mount();
        
        center = d_rotation * center;

        center += d_center;
        
        redraw();
    }

};


#endif