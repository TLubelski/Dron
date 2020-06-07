#include "Scene.hh"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

void Scene::build_scene()
{
    //---Place obstacles--
    obs_collection.push_back( std::shared_ptr<Obstacle> ( new Bottom(api,map_radius) ) );
    obs_collection.push_back( std::shared_ptr<Obstacle> ( new Water(api,map_radius) ) );
    obs_collection.push_back( std::shared_ptr<Obstacle> ( new Stone(api,{7,7,-10}, 2,2,20) ) );
    obs_collection.push_back( std::shared_ptr<Obstacle> ( new Stone(api,{12,13,-8}, 3,3,24) ) );
    obs_collection.push_back( std::shared_ptr<Obstacle> ( new Stone(api,{-10,-10,-16}, 10,10,8) ) );
    obs_collection.push_back( std::shared_ptr<Obstacle> ( new Bomb(api,{10,-10,-2},4,map_radius) ) );
    obs_collection.push_back( std::shared_ptr<Obstacle> ( new Bomb(api,{-10,11,7},4,map_radius) ) );

    //--Place drones--
    drone_collection.push_back( std::shared_ptr<DroneInterface> (new Drone(api, {0,0,0}, 3 , 4 , 1, "red") ) );
    drone_collection.push_back( std::shared_ptr<DroneInterface> (new Drone(api, {-10,4, -10}, 3, 4, 1, "purple") ) );
    drone_collection.push_back( std::shared_ptr<DroneInterface> (new Drone(api, {-15,-15, 10}, 3, 4, 1, "green") ) );
}

void Scene::control()
{
    bool session = true; //active session indicator
    int selection;

    system("clear");

    cout << "####################################" << endl
         << "# Multi-Submarine control terminal #" << endl
         << "####################################" << endl;

    while (session)
    {
        cout << "# Select drone to control: " << endl 
            << "[1]Red [2]Purple [3]Green [0]Exit" << endl << endl
            << "# ID: ";

        cin >> selection;

        switch (selection)
        {
        case 1: //correct choice
        case 2:
        case 3:
            cout << "[Info] Selected drone with id = " << selection << endl;
            drone_id = selection-1;
            main_drone = std::dynamic_pointer_cast<Drone> (drone_collection[drone_id]);
            sub_control();
            break;

        case 0: //exit
            cout << "[Info] Logged out." << endl;
            session = false;
            break;

        default: //incorrect choice
            cout << "[Error] Undefined drone id." << endl;
            break;
        }

    }

}

void Scene::sub_control()
{
    bool session = true; //active session indicator
    int input;

    double angle;
    double distance;
    double dist_to_c;

    cout << "Avaible actions:" << endl
         << "-[1]Rotate" << endl
         << "-[2]Move" << endl
         << "-[0]Change drone" << endl; 

    while(session)
    {
        cout << "\n# Command: ";
        cin >> input;
        switch (input)
        {
        case 1: //rotate
            cout << "# Angle in deg ([+]left, [-]right): ";
            cin >> angle;
            cout << "[Action] Rotating..." << endl;
            main_drone->turn( angle);
            cout << "[Info] Rotated " << fabs(angle) << "deg to the " << ( angle>0 ? "left." : "right.") << endl;
            break;
        
        case 2: //move
            cout << "# Distance ([+]forward, [-]backward): ";
            cin >> distance;
            cout << "# Climb angle in deg ([+]up, [-]down): ";
            cin >> angle;
            cout << "[Action] Moving..." << endl;
            dist_to_c = collision_control(distance, angle); //proceed collsion checking 
            cout << "[Info] Moved " << fabs(dist_to_c) << " units " << ( distance>0 ? "forward" : "backward") << " with " << angle << "deg climb angle." << endl;
            break;

        case 0: //exit
            cout << "[Info] Relogging." << endl << endl;
            session = false;
            break;

        default:
            cout << "[Error] Undefined command." << endl;
            break;
        }
    }

}

double Scene::collision_control(double distance, double angle)
{
    double dist_to_c = 0; //traveled distance
    double step = 0.1; //standard moving step
    bool collision = false;

    if(distance < 0) //backward move 
    {
        step *= (-1);
        angle = -angle;
    }

    //calculate shift
    Vector3D step_vect({0, step ,0});
    step_vect = Rotation(X_axis, angle) * step_vect;

    //movement routine
    for (double i = 0; i <= fabs(distance) && !collision; i += fabs(step))
    {
        //checking collision with static obstacles
        for(int j = 0; j < (int)drone_collection.size() && !collision; j++)
            collision = drone_collection[i]->collisionCheck( main_drone, step_vect);
    
        //checking collision with drones
        for(int j = 0; j < (int)drone_collection.size() && !collision; j++)
        {
            if(j != drone_id) //skip itself
                collision = drone_collection[i]->collisionCheck( main_drone, step_vect );
        }
        
        //move if no collision
        if( !collision )
        {
            main_drone->move_frame(step_vect);
            dist_to_c += fabs(step);   
        }
    }

    return dist_to_c; //return traveled distance
}
