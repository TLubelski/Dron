#include "Cuboid.hh"

using std::vector;

/*******************************************
 Calculationg Vertexes by dims and center
********************************************/
void Cuboid::calculateVertexArr()
{
    double x_dim = dims[0] / 2.0;
    double y_dim = dims[1] / 2.0;
    double z_dim = dims[2] / 2.0;

    /* Drawing in (0,0,0) */
    vertexArr =
    {
        { - x_dim,  - y_dim,  - z_dim}, //bottom
        { - x_dim,  + y_dim,  - z_dim},
        { + x_dim,  + y_dim,  - z_dim},
        { + x_dim,  - y_dim,  - z_dim},

        { - x_dim,  - y_dim,  + z_dim}, //top
        { - x_dim,  + y_dim,  + z_dim},
        { + x_dim,  + y_dim,  + z_dim},
        { + x_dim,  - y_dim,  + z_dim},
    };

    /* Rotation in (0,0,0) and placing*/
    for (auto &vertex : vertexArr)
        vertex = orientation * vertex + center;
} 

/*******************************************
 Redrawing methods
********************************************/
void Cuboid::draw()
{
    calculateVertexArr();

    id = api->draw_polyhedron(vector<vector<drawNS::Point3D>>{
        vector<drawNS::Point3D>(vertexArr.begin(), vertexArr.begin() + 4),
        vector<drawNS::Point3D>(vertexArr.end() - 4, vertexArr.end() ) },
        color);
}

