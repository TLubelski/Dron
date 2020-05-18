#ifndef DRAWABLE_HH
#define DRAWABLE_HH

#include "Dr3D_gnuplot_api.hh"

class Drawable
{
protected:
    std::shared_ptr<drawNS::Draw3DAPI> api;
    uint id;
    std::string color;

    Drawable(std::shared_ptr<drawNS::Draw3DAPI> _api, std::string _color = "black")
    : api(_api), color(_color){ }

public:
    Drawable() = delete;

    /***Pure virtual methods***/
    virtual void draw() = 0;
    virtual void erase() = 0;
    virtual void redraw() = 0;


};


#endif