#include "Surface.hh"

/*************** Surface:: **************/

void Surface::draw()
{
    std::vector<std::vector<drawNS::Point3D>> output;

    //copy vertexArr to Point3D vector
    for(auto vertex : vertexArr)
        output.push_back( std::vector<drawNS::Point3D>( vertex.begin(), vertex.end() ) );

    //draw surface
    api->draw_surface(output, color );
}

/*************** Bottom:: *****************/

double Bottom::noise_gen() const 
{
    double temp;
    temp = rand() % 20;
    temp /= 10.0;
    return temp;
}

void Bottom::calculateGemoetry(int radius, int grid_step)
{
    vertexArr.clear();

    double x = -radius;
    double y = -radius;

    for(int i = 0; i <= 2*radius; i+=grid_step)
    {
        std::vector<Vector3D> temp;
        for(int j = 0; j <= 2*radius; j+=grid_step)
        {
            temp.push_back( Vector3D({ x, y, noise_gen()-radius }) );
            y+=grid_step;
        }
        y = -radius;
        x+=grid_step;
        vertexArr.push_back(temp);
    }
}

bool Bottom::collisionCheck(std::shared_ptr<DroneInterface> drone, const Vector3D & step_vect) const
{
    //estimate next drone position   
    Vector3D next_pos = drone->getCenter() + drone->getOrient() * step_vect;

    //check for collision
    if( next_pos[2] <= (map_radius - drone->getZ()*0.5 ) )
        return false;
    else
    {
        std::cout << "[Warning] Drone has been surfaced. Stopping." << std::endl;
        return true;
    }
}

/*************** Water:: *****************/

double Water::wave_gen() const
{
    double result;
    static bool phase = true;
    result = (phase) ? 0 : -1;
    phase = !phase;
    return result;
}

void Water::calculateGemoetry(int radius, int grid_step)
{
    vertexArr.clear();
    
    double x = -radius;
    double y = -radius;
    double z;

    for(int i = 0; i <= 2*radius; i+=grid_step)
    {
        z = wave_gen();
        std::vector<Vector3D> temp;
        for(int j = 0; j <= 2*radius; j+=grid_step)
        {
            temp.push_back( Vector3D({ x, y, z+radius }) );
            y+= grid_step;
        }
        y = -radius;
        x+= grid_step;
        vertexArr.push_back(temp);
    }
}

bool Water::collisionCheck(std::shared_ptr<DroneInterface> drone, const Vector3D & step_vect) const
{
    //estimate next drone position   
    Vector3D next_pos = drone->getCenter() + drone->getOrient() * step_vect;
    
    //check for collision
    if( next_pos[2] >= ( -map_radius + 2 + drone->getZ()*0.5 ) )
        return false;
    else
    {
        std::cout << "[Warning] Drone too close to seabed. Stopping to avoid collision." << std::endl;
        return true;
    }
}