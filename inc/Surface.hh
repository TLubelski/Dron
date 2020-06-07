#ifndef SURFACE_HH
#define SURFACE_HH

/*!
 * \file Surface.hh
 * File contains Surface, Bottom and Water class definition
 */

#include "Vector.hh"
#include "Drawable.hh"
#include "Obstacle.hh"
#include "Drone.hh"

#include <cstdlib>
#include <ctime>

/****************************************
 \brief Class of drawable surface
*****************************************/
class Surface : public Drawable
{
protected:
    /*!
     * \brief Stores vertex locations
     */
    std::vector<std::vector<Vector3D>> vertexArr;

    /*!
     * \brief Parametric constructor
     * \param api Shared pointer to gnnuplot api
     * \param color Color of surface
     */
    Surface(std::shared_ptr<drawNS::Draw3DAPI> api, std::string color = "black")
    : Drawable(api,color) { }

public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Surface() = delete;

    /*!
     * \brief Drawing method
     */
    virtual void draw() override;
};


/****************************************
 \brief Class of bottom surface
*****************************************/
class Bottom : public Surface, public Obstacle
{
protected:
    /*!
     * \brief Return random 0.0 - 2.0
     */
    double noise_gen() const;

    /*!
     * \brief Calculate locations of vertexes
     */
    void calculateGemoetry(int radius, int grid_step);

    /*!
     * \brief Stores map size
     */
    int map_radius;

public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Bottom() = delete;    
    
     /*!
     * \brief Parametric constructor
     * \param api Shared pointer to gnnuplot api
     * \param radius Radius of map in every dimension
     */
    Bottom(std::shared_ptr<drawNS::Draw3DAPI> api, int radius)
    : Surface(api, "yellow"), map_radius(radius)
    { 
        int step = radius/10;
        if( step == 0) step = 1; //small map protection
        
        calculateGemoetry(radius, step);
        draw();
    }

    /*!
     * \brief Virtual override method to check collision with main drone
     * \param drone shared_ptr to main drone
     * \param step_vect estimiation of next drone relocation
     */
    virtual bool collisionCheck(std::shared_ptr<DroneInterface> drone, const Vector3D & step_vect) const override;

};


/****************************************
 \brief Class of water surface
*****************************************/
class Water : public Surface, public Obstacle
{
protected:
    /*!
     * \brief Return 0 or -0.5 ech call
     */
    double wave_gen() const;
    
    /*!
     * \brief Calculate locations of vertexes
     */
    void calculateGemoetry(int radius, int grid_step);

    /*!
     * \brief Stores map size
     */
    int map_radius;

public:
    /*!
     * \brief deleted non-parametric constructor to force using parametric.
     */
    Water() = delete;

     /*!
     * \brief Parametric constructor
     * \param api Shared pointer to gnnuplot api
     * \param radius Radius of map in every dimension
     */
    Water(std::shared_ptr<drawNS::Draw3DAPI> api, int radius)
    : Surface(api, "blue"), map_radius(radius)
    { 
        int step = radius/10; 
        if( step == 0) step = 1; //small map protection

        calculateGemoetry(radius, step);
        draw();
    }

    /*!
     * \brief Virtual override method to check collision with main drone
     * \param drone shared_ptr to main drone
     * \param step_vect estimiation of next drone relocation
     */
    virtual bool collisionCheck(std::shared_ptr<DroneInterface> drone, const Vector3D & step_vect) const override;

};

#endif