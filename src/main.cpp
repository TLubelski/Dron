#include <iostream>

#include "Dr3D_gnuplot_api.hh"
#include "Stone.hh"
#include "Drone.hh"

using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::cout;
using std::endl;
using std::vector;



int main()
{

    std::shared_ptr<drawNS::Draw3DAPI> api(new APIGnuPlot3D(-10, 10, -10, 10, -10, 10, 0));

    //---------------Scene build------------------------------
    Stone rock1(api, Vector3D({5,-5,-10}), 3, 4, 2);
    rock1.rotate(Rotation(Z_axis, 45));
    rock1.rotate(Rotation(X_axis, 45));

    Stone rock2(api, Vector3D({-5, 5, -10}), 1, 2, 3);
    rock2.rotate(Rotation(Z_axis, 45));
    rock2.rotate(Rotation(X_axis, 45));

    Stone rock3(api, Vector3D({4, -2, -10}), 2 , 2, 2);
    rock3.rotate(Rotation(Z_axis, 45));
    rock3.rotate(Rotation(X_axis, 45));

    rock1.draw();
    rock2.draw();
    rock3.draw();

    //---------------Controling------------------------------
    Drone submarine(api);

    submarine.control_panel();

}
