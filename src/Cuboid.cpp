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
    //floor
    vertexArr[0] = Vector3D({ - x_dim,  - y_dim,  - z_dim});
    vertexArr[1] = Vector3D({ - x_dim,  + y_dim,  - z_dim});
    vertexArr[2] = Vector3D({ + x_dim,  + y_dim,  - z_dim});
    vertexArr[3] = Vector3D({ + x_dim,  - y_dim,  - z_dim});
    //roof
    vertexArr[4] = Vector3D({ - x_dim,  - y_dim,  + z_dim});
    vertexArr[5] = Vector3D({ - x_dim,  + y_dim,  + z_dim});
    vertexArr[6] = Vector3D({ + x_dim,  + y_dim,  + z_dim});
    vertexArr[7] = Vector3D({ + x_dim,  - y_dim,  + z_dim});

    /* Rotation in (0,0,0) */
    for (int i = 0; i < 8; i++)
        vertexArr[i] = orientation * vertexArr[i];

    /* Placing in space */
    for (int i = 0; i < 8; i++)
        vertexArr[i] += center;
} 

/*******************************************
 Redrawing methods
********************************************/
void Cuboid::draw()
{
    calculateVertexArr();

    id = api->draw_polyhedron(vector<vector<drawNS::Point3D>>{
        {vertexArr[0], vertexArr[1], vertexArr[2], vertexArr[3]},
        {vertexArr[4], vertexArr[5], vertexArr[6], vertexArr[7]}},
        color);
}
