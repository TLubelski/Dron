#include "Sphere.hh"
#include <cmath>


void Sphere::draw()
{
    std::vector<std::vector<drawNS::Point3D>> output;

    //draw upper part
    for(auto vertex : assembly_up)
        output.push_back( std::vector<drawNS::Point3D>( vertex.begin(), vertex.end() ) );
    api->draw_surface(output, color );

    output.clear();

    //draw lower part
    for(auto vertex : assembly_down)
        output.push_back( std::vector<drawNS::Point3D>( vertex.begin(), vertex.end() ) );
    api->draw_surface(output, color );
}

void Sphere::calculateGeometry()
{
    assembly_up.clear();
    assembly_down.clear();

    double r = radius;
    double r2 = radius/sqrt(2);
    double a22 = 22.5*3.14/180;
    double a45 = 45*3.14/180;

    //fill 5x5 surface (5 vectors of 5 vectors of Vectors)
    std::vector<Vector3D> temp;

    temp.push_back({-r*cos(a45), r*sin(a45), 0});
    temp.push_back({-r*cos(a22), r*sin(a22), 0});
    temp.push_back({-r,0,0});
    temp.push_back({-r*cos(a22), -r*sin(a22), 0});
    temp.push_back({-r*cos(a45), -r*sin(a45), 0});
    
    assembly_up.push_back(temp);
    assembly_down.push_back(temp);
    
    temp.clear();
    
    temp.push_back({-r*sin(a22), r*cos(a22), 0});
    temp.push_back({-r2*cos(a45), r2*sin(a45), r2});
    temp.push_back({-r2,0,r2});
    temp.push_back({-r2*cos(a45), -r2*sin(a45), r2});
    temp.push_back({-r*sin(a22), -r*cos(a22), 0});

    assembly_up.push_back(temp);
    assembly_down.push_back(temp);

    temp.clear();
    
    temp.push_back({0, r, 0});
    temp.push_back({0, r2, r2});
    temp.push_back({0,0,r});
    temp.push_back({0, -r2, r2});
    temp.push_back({0, -r, 0});

    assembly_up.push_back(temp);
    assembly_down.push_back(temp);

    temp.clear();
    
    temp.push_back({r*sin(a22), r*cos(a22), 0});
    temp.push_back({r2*cos(a45), r2*sin(a45), r2});
    temp.push_back({r2,0,r2});
    temp.push_back({r2*cos(a45), -r2*sin(a45), r2});
    temp.push_back({r*sin(a22), -r*cos(a22), 0});

    assembly_up.push_back(temp);
    assembly_down.push_back(temp);

    temp.clear();
    
    temp.push_back({r*cos(a45), r*sin(a45), 0});
    temp.push_back({r*cos(a22), r*sin(a22), 0});
    temp.push_back({r,0,0});
    temp.push_back({r*cos(a22), -r*sin(a22), 0});
    temp.push_back({r*cos(a45), -r*sin(a45), 0});

    assembly_up.push_back(temp);
    assembly_down.push_back(temp);

    //mirror down assembly part
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            assembly_down[i][j][2] *= (-1); 
    
    //locate in space
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
        {
            assembly_up[i][j] += center;
            assembly_down[i][j] += center;
        }

}






