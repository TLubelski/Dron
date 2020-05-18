#ifndef SCENE_HH
#define SCENE_HH

#include "Surface.hh"

class Scene
{
private:
    Bottom bottom;
    Water water;

public:
    Scene() = delete;
    
    Scene(std::shared_ptr<drawNS::Draw3DAPI> api, int radius)
    : bottom(api, radius), water(api, radius)
    {
        api->redraw();
    }
};

#endif