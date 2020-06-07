#ifndef SCREW_HH
#define SCREW_HH

/*!
 * \file Screw.hh
 * File contains Screw class definition
 */

#include "Hexagon.hh"

/*!
* \brief Enum to set side of screw
*/
enum Side{side_L, side_R};

/****************************
 \brief Class rotating screw
****************************/
class Screw : public Hexagon
{
private:
    /*!
     * \brief Side of drone to mount on
     */
    const Side side;
    
    /*!
     * \brief Saved angle of screw
     */
    int screw_angle = 0;
    
    /*!
     * \brief Step angle to rotate per frame
     */
    int step = 10;
    
    /*!
     * \brief Position in reference to drone
     */
    Vector3D screw2drone;

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
        : Hexagon(_api, d_center, d_dim_Y/4.0, d_dim_Z/2.0, color), side(_side)
        { 
            screw2drone[1] = -(d_dim_Y/2.0 + height/2.0); //mount to back
                
            if( side == side_L ) //mount to left
            {
                screw2drone[0] = -(d_dim_X/2.0 - radius);
            }
            else //mount to right
            {
                screw2drone[0] = (d_dim_X/2.0 - radius);
                step = -step;
            }
            rotate(Rotation(X_axis, 90));
            center = d_center + screw2drone;

            draw();
        }    

    /*!
     * \brief Calculates screws for 1 frame
     * \param d_center Center point of Drone
     * \param d_rotation Rotation matrix of Drone
     * \param working Is now rotating
     */
    void animate_frame(Vector3D d_center, Rotation d_rotation, bool working = true)
    {
        if(working)
        {
            screw_angle += step;
            if( abs(screw_angle) == 360)
                screw_angle = 0;
        }

        center = d_center + d_rotation * screw2drone; //calculate position
        orientation =  d_rotation * Rotation(X_axis,90) * Rotation(Z_axis, screw_angle); //calculate orientation
        
        redraw();
    }

};

#endif