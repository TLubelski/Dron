#ifndef OBSTACLE_HH
#define OBSTACLE_HH

/*!
 * \file Obstacle.hh
 * File contains Obstacle abstract class definition
 */

#include "Vector.hh"

class DroneInterface;

/*********************************
 \brief Abstract obsctacle class
**********************************/
class Obstacle
{
public:
    /*!
     * \brief pure virtual method for checking collision with drone
     * \param drone shared_ptr to main drone
     * \param step_vect estimiation of next drone relocation
     */
    virtual bool collisionCheck(std::shared_ptr<DroneInterface>, const Vector3D & step_vect ) const = 0;
};

#endif