#ifndef STONE_HH
#define STONE_HH

#include "Obstacle.hh"
#include "Drone.hh"

#include <iostream>

/**************************
 \brief Just standing rock
**************************/
class Stone : public Cuboid, public Obstacle
{
private:
    /*!
     * \brief Horizontal radius of stone
     */
    double getR() const
    {
        return sqrt( pow(0.5*dims[0],2) + pow(0.5*dims[1],2) );
    }

public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Stone() = delete;

    /*!
     * \brief Full parametric constructor
     * \param _api shared pointer to gnuplot api
     * \param _center point to spawn stone
     * \param x_dim X dimension of stone
     * \param y_dim Y dimension of stone
     * \param z_dim Z dimension of stone
     */
    Stone(std::shared_ptr<drawNS::Draw3DAPI> _api, Vector3D _center, double x_dim, double y_dim, double z_dim)
        : Cuboid(_api, _center, x_dim, y_dim, z_dim, "grey")
        { 
            draw(); 
        }

    /*!
     * \brief Virtual override method to check collision with main drone
     * \param drone shared_ptr to main drone
     * \param step_vect estimiation of next drone relocation
     */
    virtual bool collisionCheck(std::shared_ptr<DroneInterface> drone, const Vector3D & step_vect) const override
    {
        //estimate next drone position       
        Vector3D next_pos = drone->getCenter() + drone->getOrient() * step_vect;

        //calculate distances
        double V_dist = (next_pos[2]-drone->getZ()*0.5) - (center[2] + dims[2]*0.5); 
        double H_dist = sqrt( pow(next_pos[0] - center[0],2) + pow(next_pos[1] - center[1],2) );

        //Stone V and H collsion checking
        if( H_dist >= drone->getR() + getR() )
            return false; 
        else if( V_dist > 0.5)
            return false;
        
        //Message
        std::cout << "[Warning] Stone detected! Stopping to avoid collision." << std::endl;
        return true;
    }
};

#endif