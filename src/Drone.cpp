#include "Drone.hh"

#include <unistd.h>


/*******************************************
 Collision methods
********************************************/
double Drone::getR() const
{
    return Vector3D({ 0.5*dims[0], 0.75*dims[1], 0.5*dims[2] }).length();
}

bool Drone::collisionCheck(std::shared_ptr<DroneInterface> drone, const Vector3D & step_vect) const
{
    //estimate next drone position
    Vector3D next_pos = drone->getCenter() + drone->getOrient() * step_vect;
    
     //calculate distances
    double V_dist = fabs(next_pos[2] - center[2]); 
    double H_dist = sqrt( pow(next_pos[0] - center[0],2) + pow(next_pos[1] - center[1],2) );

    //Drone V and H collsion checking
    if( H_dist + 0.5 >= drone->getR() + getR())
        return false; 
    else if( V_dist >= getZ()*0.5 + dims[2]*0.5 + 0.5)
        return false;
        
    //Message
    std::cout << "[Warning] Another drone detected! Stopping to avoid collision." << std::endl;
    return true;
}

/*******************************************
 Movement methods
********************************************/
void Drone::turn(double angle)
{
    bool work_L = false;
    bool work_R = false;
    double step = 1;
    
    if(angle < 0)  //right rotation 
    {
        step *= (-1);
        work_L = true;
    }
    else
        work_R = true;
    

    for(double i = 0; i <= fabs(angle); i += fabs(step))
    {
        rotate(Rotation(Z_axis, step));
        redraw();
        screw_R.animate_frame(center, orientation, work_R);
        screw_L.animate_frame(center, orientation, work_L);
        api->redraw();
        next_frame();
    }
}

void Drone::move_frame(const Vector3D & step_vect)
{   
    relocate( step_vect );
    redraw();
    screw_R.animate_frame(center, orientation);
    screw_L.animate_frame(center, orientation);
    api->redraw();
    next_frame();
}

/*******************************************
 Timing method
********************************************/
#define FPS 60

void Drone::next_frame() const
{ 
    usleep(1000000/FPS); 
}