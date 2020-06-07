#ifndef DRONE_HH
#define DRONE_HH

/*!
 * \file Drone.hh
 * File contains drone and drone interface class definition
 */

#include "Cuboid.hh"
#include "Screw.hh"
#include "Obstacle.hh"

/***************************************************
 \brief Class of DroneInterface (used in collisions)
****************************************************/
class DroneInterface
{
public:
    /*!
     * \brief Pure Virtual Getter of center point
     */
    virtual Vector3D getCenter() const = 0;
    
    /*!
     * \brief Pure Virtual Getter of drone orientation matrix
     */
    virtual Rotation getOrient() const = 0;

    /*!
     * \brief Pure Virtual Getter of drone Z dimension
     */
    virtual double getZ() const = 0;

    /*!
     * \brief Pure Virtual Getter of shape radius
     */
    virtual double getR() const = 0;

    /*!
     * \brief Pure Virtual method for checking collision with another drones
     * \param drone shared_ptr to main drone
     * \param step_vect estimiation of next drone relocation
     */
    virtual bool collisionCheck(std::shared_ptr<DroneInterface> drone, const Vector3D & step_vect) const = 0;
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
    Drone(std::shared_ptr<drawNS::Draw3DAPI> _api, Vector3D _center, double x_dim, double y_dim, double z_dim, std::string color = "black")
        : Cuboid(_api, _center, x_dim, y_dim, z_dim, color),
            screw_L(_api, center, x_dim, y_dim, z_dim, side_L, color),
            screw_R(_api, center, x_dim, y_dim, z_dim, side_R, color)
        { 
            draw(); 
        }

    /*!
     * \brief Turning Drone with animation
     * \param angle Angle of rotation in deg
     */
    void turn( double angle);

    /*!
     * \brief Moving 1 frame of drone animation
     * \param step distance to go
     * \param angle Angle of climbing in deg
     */
    void move_frame( const Vector3D & step_vect);

    /*!
     * \brief Virtual Getter override of center point
     */
    virtual Vector3D getCenter() const override
        { return center; }

    /*!
     * \brief Virtual Getter override of drone orientation matrix
     */
    virtual Rotation getOrient() const override
        { return orientation; }

    /*!
     * \brief Virtual Getter override of drone Z dimension
     */
    virtual double getZ() const override
        { return dims[2]; }

    /*!
     * \brief Virtual Getter override of shape radius
     */
    virtual double getR() const;

    /*!
     * \brief Virtual method override for checking collision with another drones
     * \param drone shared_ptr to main drone
     * \param step_vect estimiation of next drone relocation
     */
    virtual bool collisionCheck(std::shared_ptr<DroneInterface> drone, const Vector3D & step_vect) const override;


};


#endif