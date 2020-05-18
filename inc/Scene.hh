#ifndef SCENE_HH
#define SCENE_HH

#include "Surface.hh"
#include "Stone.hh"


/*********************************************
 \brief Class of drawing scene
**********************************************/
class Scene
{
private:
    /*!
     * \brief Random generated ocean bottom
     */
    Bottom bottom;
    
    /*!
     * \brief Wavy water surface
     */
    Water water;
    
    /*!
     * \brief Decoration
     */
    Stone rock;

public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Scene() = delete;
    
    /*!
     * \brief Parametric constructor, also draws objects
     * \param api shared pointer to gnuplot api
     * \param radius Radius of map in every dimension
     */
    Scene(std::shared_ptr<drawNS::Draw3DAPI> api, int radius)
    : bottom(api, radius), water(api, radius),
        rock(api, Vector3D({5, 5, -8}), 2, 2 ,2)
    {
        rock.rotate(Rotation(X_axis, 45));
        rock.rotate(Rotation(Y_axis, 45));
        rock.draw();
        api->redraw();
    }
};

#endif