#include "Hexagon.hh"

using std::vector;

/*******************************************
 Calculationg Vertexes by dims and center
********************************************/
void Hexagon::calculateVertexArr()
{
    double h = height/2; //half of height
    double r = radius; //radius of hexagon
    double a = (r*sqrt(3))/2; //hexagon side
    double b = a/2; //half of hexagon side

    /* Drawing in (0,0,0) */
    vertexArr =
    { 
        { 0, -r, -h }, //bottom
        { -a, -b, -h },
        { -a, b, -h },
        { 0, r, -h },
        { a, b, -h },
        { a, -b, -h },
     
        { 0, -r, h }, //top
        { -a, -b, h },
        { -a, b, h },
        { 0, r, h },
        { a, b, h },
        { a, -b, h },
    };

    /* Rotation in (0,0,0) and placing */
    for (auto &vertex : vertexArr)
        vertex = orientation * vertex + center;

} 

/*******************************************
 Drawing method
********************************************/
void Hexagon::draw()
{
    calculateVertexArr();

    id = api->draw_polyhedron(vector<vector<drawNS::Point3D>>{
        vector<drawNS::Point3D>(vertexArr.begin(), vertexArr.begin() + 6 ),
        vector<drawNS::Point3D>(vertexArr.end() - 6, vertexArr.end() ) },
        color);
}