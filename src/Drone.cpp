#include "Drone.hh"

#include <iostream>
#include <cstdlib>

using namespace std;

void wait4key()
{
    do
    {
        std::cout << "\n Press a key to continue..." << std::endl;
    } while (std::cin.get() != '\n');
}

/*********************************
 Main Control panel
**********************************/
void Drone::control_panel()
{
    bool session = true;
    int input;

    char axis;
    double angle;
    double distance;

    while(session)
    {
        system("clear");
        cout << "###################################" << endl
             << "# Submarine control terminal v0.1 #" << endl
             << "###################################" << endl
             << "#Availbe operations:" << endl
             << "-[1]Rotate" << endl
             << "-[2]Move" << endl
             << "-[0]Exit" << endl
             << "#Command:"<< endl;

        cin >> input;
        switch (input)
        {
        case 1: //rotate
            cout << "#Axis(x,y,z):";
            cin >> axis;
            cout << "#Angle(degree):";
            cin >> angle;
            turn( axis, angle);
            cout << "[Info] Rotated " << angle << "degrees around " << axis <<" axis." << endl;
            wait4key();
            break;
        
        case 2: //move
            cout << "#Distance:";
            cin >> distance;
            move(distance);
            cout << "[Info] Moved "<< distance << "units in X-axis." << endl;
            wait4key();
            break;

        case 0: //exit
            cout << "[Info] Logged out." << endl;
            wait4key();
            session = false;
            break;

        default:
            cout << "[Error] Undefined command." << endl;
            wait4key();
            break;
        }
    }
}

/*******************************************
 Movement methods
********************************************/
void Drone::turn(char axis, double angle)
{
    rotate( Rotation((Axis)axis, angle));
    redraw();
}

void Drone::move(double distance)
{
    relocate(Vector3D({distance, 0, 0}));
    redraw();
}