#include "Drone.hh"

#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

#define FPS 60

void next_frame()
{ 
    usleep(1000000/FPS); 
}

void wait4key()
{
    do
    {
        std::cout << "\n Press a key to continue..." << std::endl;
    } 
    while (std::cin.get() != '\n');
}

/*********************************
 Main Control panel
**********************************/
void Drone::control_panel()
{
    bool session = true;
    int input;

    double angle;
    double distance;

    system("clear");

    cout << "###################################" << endl
         << "# Submarine control terminal v0.1 #" << endl
         << "###################################" << endl
         << "Avaible actions:" << endl
         << "-[1]Rotate" << endl
         << "-[2]Move" << endl
         << "-[0]Exit" << endl; 

    while(session)
    {
        cout << "\n#Command: ";
        cin >> input;
        switch (input)
        {
        case 1: //rotate
            cout << "#Angle ([+]left, [-]right):";
            cin >> angle;
            cout << "[Action] Rotating..." << endl;
            turn( angle);
            cout << "[Info] Rotated " << fabs(angle) << "deg to the " << ( angle>0 ? "left." : "right.") << endl;
            break;
        
        case 2: //move
            cout << "#Distance ([+]forward, [-]backward):";
            cin >> distance;
            cout << "#Climb angle ([+]up, [-]down):";
            cin >> angle;
            cout << "[Action] Moving..." << endl;
            move(distance, angle);
            cout << "[Info] Moved " << fabs(distance) << " units " << ( distance>0 ? "forward" : "backward") << " with " << angle << "deg angle." << endl;
            break;

        case 0: //exit
            cout << "[Info] Logged out." << endl;
            session = false;
            break;

        default:
            cout << "[Error] Undefined command." << endl;
            break;
        }
    }
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
        screw_R.animate_t(center, orientation, work_R);
        screw_L.animate_t(center, orientation, work_L);
        api->redraw();
        next_frame();
    }
}

void Drone::move(double distance, double angle)
{
    double step = 0.1;
    if(distance < 0) step *= (-1); //backward move 
    Vector3D step_vect({0, step ,0});
    step_vect = Rotation(X_axis, angle) * step_vect;

    for (double i = 0; i <= fabs(distance); i += fabs(step))
    {   
        relocate( step_vect );
        redraw();
        screw_R.animate_m(step_vect);
        screw_L.animate_m(step_vect);
        api->redraw();
        next_frame();
    }
}