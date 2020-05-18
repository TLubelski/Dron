#include "Surface.hh"

/*************** Surface:: **************/

void Surface::draw()
{
    std::vector<std::vector<drawNS::Point3D>> output;

    for(auto i : vertexArr)
        output.push_back( std::vector<drawNS::Point3D>( i.begin(), i.end() ) );

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

void Bottom::calculateGemoetry(int radius)
{
    double x = -radius;
    double y = -radius;

    for(int i = 0; i <= 2*radius; i++)
    {
        std::vector<Vector3D> temp;
        for(int j = 0; j <= 2*radius; j++)
        {
            temp.push_back( Vector3D({ x, y, noise_gen()-radius }) );
            y++;
        }
        y = -radius;
        x++;
        vertexArr.push_back(temp);
    }
}

/*************** Water:: *****************/

double Water::wave_gen() const
{
    double result;
    static bool phase = true;
    result = (phase) ? 0 : -0.5;
    phase = !phase;
    return result;
}

void Water::calculateGemoetry(int radius)
{
   double x = -radius;
        double y = -radius;
        double z;

        for(int i = 0; i <= 2*radius; i++)
        {
            z = wave_gen();
            std::vector<Vector3D> temp;
            for(int j = 0; j <= 2*radius; j++)
            {
                temp.push_back( Vector3D({ x, y, z+radius }) );
                y++;
            }
            y = -radius;
            x++;
            vertexArr.push_back(temp);
        }
}