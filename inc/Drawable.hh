#ifndef DRAWABLE_HH
#define DRAWABLE_HH

#include "Dr3D_gnuplot_api.hh"


/*****************************************
 \brief Class of drawable geometry object 
******************************************/
class Drawable
{
protected:
    /*!
     * \brief Shared pointer to gnuplot drawing api
     */
    std::shared_ptr<drawNS::Draw3DAPI> api;
    
    /*!
     * \brief Unique identifier for figure
     */
    uint id;
    
    /*!
     * \brief Color of drawing
     */
    std::string color;
    
    /*!
     * \brief Full parametric constructor
     * \param _api shared pointer to gnuplot api
     * \param _color Color of figure
     */
    Drawable(std::shared_ptr<drawNS::Draw3DAPI> _api, std::string _color = "black")
    : api(_api), color(_color){ }

public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Drawable() = delete;

    /*!
     * \brief Pure virtual method of drawing figure. Must be specified in dervatives.
     */
    virtual void draw() = 0;
    
    /*!
     * \brief Erase figure from scene
     */
    virtual void erase()
    {
        api->erase_shape(id);
    }
    
    /*!
     * \brief Erase figure and draw again
     */
    virtual void redraw()
    {
        erase();
        draw();
    }

};


#endif