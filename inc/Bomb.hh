#ifndef BOMB_HH
#define BOMB_HH

/*!
 * \file Bomb.hh
 * File contains Bomb class definition
 */

#include "Sphere.hh"
#include "Obstacle.hh"
#include "Drone.hh"

/*********************************************
 \brief Class of sea Boomb
**********************************************/
class Bomb : public Sphere, public Obstacle
{
public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Bomb() = delete;

    /*!
     * \brief Full parametric constructor
     * \param _api shared pointer to gnuplot api
     * \param _center center point of figure
     * \param _radius radius of sphere
     * \param _color Color of figure
     */
    Bomb( std::shared_ptr<drawNS::Draw3DAPI>  _api, Vector3D _center, double _radius, double map, std::string _color = "black" )
    : Sphere(_api, _center, _radius, _color)
    {
        //draw chain
        api->draw_line(drawNS::Point3D(center[0], center[1], center[2]-radius ), drawNS::Point3D( center[0],center[1], -map) );
    }

    /*!
     * \brief Virtual override method to check collision with main drone
     * \param drone shared_ptr to main drone
     * \param step_vect estimiation of next drone relocation
     */
    virtual bool collisionCheck(std::shared_ptr<DroneInterface> drone, const Vector3D & step_vect) const override
    {
        bool col = false; //collsion flag

        //estimate next drone position
        Vector3D next_pos = drone->getCenter() + drone->getOrient() * step_vect;

        //calculate distances
        double ball_dist = Vector3D(next_pos - center).length();
        double chain_V_dist = (next_pos[2]-drone->getZ()*0.5) - center[2]; 
        double chain_H_dist = sqrt( pow(next_pos[0] - center[0],2) + pow(next_pos[1] - center[1],2) );

        //Bomb sphere checking
        if( ball_dist <= (drone->getR() + radius + 0.5) )
            col = true;

        //Bomb chain checking
        if( chain_H_dist <= drone->getR() + 0.5 && chain_V_dist <= 0.5 )
            col = true;

        //Message
        if(col)
            std::cout << "[Warning] Bomb detected! Stopping to avoid explosion." << std::endl;

        return col;
    }

};

#endif