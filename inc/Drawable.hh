#ifndef DRAWABLE_HH
#define DRAWABLE_HH

/*!
 * \file Drawable.hh
 * File contains Drawable class definition
 */

#include "Dr3D_gnuplot_api.hh"

/*****************************************
 \brief Class of drawable geometry object 
******************************************/
class Drawable
{
protected:
    /*!
     * \brief Stores total quantity of created objects
     */
    static inline unsigned int created = 0;
    
    /*!
     * \brief Stores quantity of objects on scene
     */
    static inline unsigned int existing = 0;

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
    : api(_api), color(_color)
    { 
        created++;
        existing++;
    }

    /*!
     * \brief copy constructor
     */
    Drawable(const Drawable & arg)
        : api(arg.api), color(arg.color)
    {
        created++;
        existing++;
    }

    /*!
     * \brief default destructor
     */
    ~Drawable()
    {
        existing--;
    }

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

    /*!
     * \brief Getter of total created objects
     */
    static int getCreated()
        { return created; }
    
    /*!
     * \brief Getter of total existing objects
     */
    static int getExisting()
        { return existing; }

};

#endif