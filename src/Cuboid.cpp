#include "Cuboid.hh"
using std::vector;

/*******************************************
 Calculationg Vertexes by dims and center
********************************************/
void Cuboid::calculateVertexArr(double x_dim, double y_dim, double z_dim)
{
    x_dim /= 2.0;
    y_dim /= 2.0;
    z_dim /= 2.0;

    //floor
    vertexArr[0] = Vector3D({center[0] - x_dim, center[1] - y_dim, center[2] - z_dim});
    vertexArr[1] = Vector3D({center[0] - x_dim, center[1] + y_dim, center[2] - z_dim});
    vertexArr[2] = Vector3D({center[0] + x_dim, center[1] + y_dim, center[2] - z_dim});
    vertexArr[3] = Vector3D({center[0] + x_dim, center[1] - y_dim, center[2] - z_dim});
    
    //roof
    vertexArr[4] = Vector3D({center[0] - x_dim, center[1] - y_dim, center[2] + z_dim});
    vertexArr[5] = Vector3D({center[0] - x_dim, center[1] + y_dim, center[2] + z_dim});
    vertexArr[6] = Vector3D({center[0] + x_dim, center[1] + y_dim, center[2] + z_dim});
    vertexArr[7] = Vector3D({center[0] + x_dim, center[1] - y_dim, center[2] + z_dim});
}

/*******************************************
 Redrawing methods
********************************************/
void Cuboid::draw()
{
    id = api->draw_polyhedron(vector<vector<drawNS::Point3D>>{
        {vertexArr[0].P3D(), vertexArr[1].P3D(), vertexArr[2].P3D(), vertexArr[3].P3D()},
        {vertexArr[4].P3D(), vertexArr[5].P3D(), vertexArr[6].P3D(), vertexArr[7].P3D()}},
        color);
}

void Cuboid::erase()
{
    api->erase_shape(id);
}

void Cuboid::redraw()
{
    erase();
    draw();
}

/*******************************************
 Relocation methods
********************************************/
void Cuboid::rotate(const Rotation &r_matrix)
{
    for (int i = 0; i < 8; i++)
        vertexArr[i] = r_matrix * vertexArr[i];
    //orientation = orientation * r_matrix;

}

void Cuboid::relocate(const Vector3D &shift)
{
    for (int i = 0; i < 8; i++)
        vertexArr[i] += shift;
}
