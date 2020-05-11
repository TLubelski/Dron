#ifndef DRONE_HH
#define DRONE_HH

#include "Cuboid.hh"

void wait4key();

/*********************************
 Class of Drone control interface
**********************************/
class DroneInterface
{
public:
    DroneInterface(){}
    virtual void control_panel() = 0;
};

/********************
 Class of Drone
*********************/
class Drone : public Cuboid, public DroneInterface
{
public:
    Drone(std::shared_ptr<drawNS::Draw3DAPI> _api)
        : Cuboid(_api, Vector3D({0,0,0}), 3, 4, 1, "red"){ draw(); }

    void control_panel() override;

    void turn( char axis, double angle);

    void move( double distance );

};

#endif