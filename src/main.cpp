#include <iostream>

#include "Dr3D_gnuplot_api.hh"
#include "Drone.hh"
#include "Scene.hh"


using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::cout;
using std::endl;
using std::vector;


int main()
{
    srand(time(NULL)); //for random generation
    int map_radius = 20;
    std::shared_ptr<drawNS::Draw3DAPI> api(new APIGnuPlot3D(-map_radius, map_radius, -map_radius, map_radius, -map_radius, map_radius, -1));

    //---------------Scene build------------------------------
    Scene(api, map_radius);

    //---------------Controling------------------------------
    Drone submarine(api,3,4,1);

    submarine.control_panel();

}
