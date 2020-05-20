#ifndef DRONE_HH
#define DRONE_HH

/*!
 * \file Drone.hh
 * File contains drone and drone interface class definition
 */

#include "Cuboid.hh"
#include "Screw.hh"

/*********************************************
 \brief Class of Drone control interface [WIP]
**********************************************/
class DroneInterface
{
public:
    DroneInterface(){}
    virtual void control_panel() = 0;
};


/*************************
 \brief Class of Drone
*************************/
class Drone : public Cuboid, public DroneInterface
{
protected:
    /*!
     * \brief Left moving screw
     */
    Screw screw_L;

    /*!
     * \brief Right moving screw
     */
    Screw screw_R;

    /*!
     * \brief Method to wait for next frame
     */
    void next_frame() const;


public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Drone() = delete;

    /*!
     * \brief Full parametric constructor
     * \param _api shared pointer to gnuplot api
     * \param x_dim X dimension of Drone figure
     * \param y_dim Y dimension of Drone figure
     * \param z_dim Z dimension of Drone figure
     * \param color Color of Drone
     */
    Drone(std::shared_ptr<drawNS::Draw3DAPI> _api, double x_dim, double y_dim, double z_dim, std::string color = "black")
        : Cuboid(_api, Vector3D({0,0,0}), x_dim, y_dim, z_dim, color),
            screw_L(_api, center, x_dim, y_dim, z_dim, side_L, color),
            screw_R(_api, center, x_dim, y_dim, z_dim, side_R, color)
        { 
            draw(); 
            api->redraw(); 
        }

    /*!
     * \brief Main command line of Drone
     */
    void control_panel() override;

    /*!
     * \brief Turning Drone with animation
     * \param angle Angle of rotation in deg
     */
    void turn( double angle);

    /*!
     * \brief Moving Drone with animation
     * \param distance Distance to move
     * \param angle Angle of climbing in deg
     */
    void move( double distance, double angle );
};


#endif