#ifndef SURFACE_HH
#define SURFACE_HH

#include "Vector.hh"
#include "Drawable.hh"

#include <cstdlib>
#include <ctime>


class Surface : public Drawable
{
protected:
    std::vector<std::vector<Vector3D>> vertexArr;

    Surface(std::shared_ptr<drawNS::Draw3DAPI> api, std::string color = "black")
    : Drawable(api,color) { }

public:
    Surface() = delete;

    virtual void draw() override
    {
        std::vector<std::vector<drawNS::Point3D>> output;

        for(auto i : vertexArr)
            output.push_back( std::vector<drawNS::Point3D>( i.begin(), i.end() ) );

        api->draw_surface(output, color );
    }

    virtual void erase() override
    {
        api->erase_shape(id);
    }

    virtual void redraw() override
    {
        erase();
        draw();
    }
};


class Bottom : public Surface
{
protected:
    double noise_gen() const //return random 0-2
    {
        double temp;
        temp = rand() % 20;
        temp /= 10.0;
        return temp;
    }

public:
    Bottom() = delete;    
    
    Bottom(std::shared_ptr<drawNS::Draw3DAPI> api, int radius)
    : Surface(api, "yellow")
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
        draw();
    }

};


class Water : public Surface
{
protected:
    double wave_gen() const
    {
        double result;
        static bool phase = true;
        result = (phase) ? 0 : -0.5;
        phase = !phase;
        return result;
    }

public:
    Water() = delete;

    Water(std::shared_ptr<drawNS::Draw3DAPI> api, int radius)
    : Surface(api, "blue") 
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
        draw();
    }
};

 
#endif