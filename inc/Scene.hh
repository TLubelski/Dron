#ifndef SCENE_HH
#define SCENE_HH

/*!
 * \file Scene.hh
 * File contains Scene class definition
 */
#include "Dr3D_gnuplot_api.hh"

#include "Obstacle.hh"
#include "Surface.hh"

#include "Drone.hh"
#include "Stone.hh"
#include "Bomb.hh"

/*********************************************
 \brief Class of drawing scene
**********************************************/
class Scene
{
private:
    /*!
     * \brief Stores size of map
     */
    double map_radius;

    /*!
     * \brief Shared pointer to gnuplot drawing api
     */
    std::shared_ptr<drawNS::Draw3DAPI> api;

    /*!
     * \brief Collection of obstacles in scene (bottom, water, obstacles)
     */
    std::vector< std::shared_ptr<Obstacle> > obs_collection;

    /*!
     * \brief Collection of drones in scene
     */
    std::vector< std::shared_ptr<DroneInterface> > drone_collection;

    /*!
     * \brief Main drone pointer
     */
    std::shared_ptr<Drone> main_drone;

    /*!
     * \brief Setup objects on scene
     */
    void build_scene();

    /*!
     * \brief Current drone id
     */
    int drone_id;

    /*!
     * \brief Control of single drone
     */
    void sub_control();

    /*!
     * \brief Movement with collision checking
     * \return Distance without collision
     */
    double collision_control(double distance, double angle);

public:
    /*!
     * \brief Non-parametric constructor, also draws objects
     */
    Scene()
    : map_radius(20),
        api(new drawNS::APIGnuPlot3D(-map_radius, map_radius, -map_radius, map_radius, -map_radius, map_radius, -1) )
    {   
        build_scene();

        api->redraw();
    }

    /*!
     * \brief Start controlling drones
     */
    void control();

};

#endif