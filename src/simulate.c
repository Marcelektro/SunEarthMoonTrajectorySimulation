#include "simulate.h"

#include <math.h>


/**
 * Perform midpoint method for numerical integration.
 *
 * @param dt       Delta time
 *
 * @param accel_x  X-acceleration of the object
 * @param accel_y  Y-acceleration of the object
 *
 * @param x        X-pos of the object
 * @param y        Y-pos of the object
 *
 * @param dx_dt    X-velocity of the object
 * @param dy_dt    Y-velocity of the object
 */
void perform_midpoint_method(const double dt,
                             const double accel_x, const double accel_y,
                             double *x, double *y,
                             double *dx_dt, double *dy_dt) {

    const double dx_half = *dx_dt + 0.5 * dt * accel_x;
    *x += dt * dx_half;
    *dx_dt += dt * accel_x;

    const double dy_half = *dy_dt + 0.5 * dt * accel_y;
    *y += dt * dy_half;
    *dy_dt += dt * accel_y;

}


/**
 * Initialize simulation entities with their initial positions, velocities,
 * and accelerations. Use properties for constants.
 */
void initialize_simulation(Entity *sun, Entity *earth, Entity *moon,
                           const Properties *props) {
    // init the sun
    sun->position.x = 0.0;
    sun->position.y = 0.0;
    sun->velocity.x = 0.0;
    sun->velocity.y = 0.0;
    sun->acceleration.x = 0.0;
    sun->acceleration.y = 0.0;
    sun->mass = props->mass_sun;

    // init the earth
    earth->position.x = props->distance_earth_sun;
    earth->position.y = 0.0;
    earth->velocity.x = 0.0;
    earth->velocity.y = sqrt(props->gravity * props->mass_sun / props->distance_earth_sun);
    earth->acceleration.x = 0.0;
    earth->acceleration.y = 0.0;
    earth->mass = props->mass_earth;

    // init the moon
    moon->position.x = earth->position.x + props->distance_earth_moon;
    moon->position.y = 0.0;
    moon->velocity.x = 0.0;
    moon->velocity.y = earth->velocity.y + sqrt(props->gravity * props->mass_earth / props->distance_earth_moon);
    moon->acceleration.x = 0.0;
    moon->acceleration.y = 0.0;
    moon->mass = props->mass_moon;

}


/**
 * Calculate the gravitational acceleration between two entities.
 *
 * @param entity1   Entity to be updated
 * @param entity2   Entity to calculate the gravitational force from
 * @param props     Properties for constants
 * @param accel_x   X-acceleration of the object
 * @param accel_y   Y-acceleration of the object
 */
void calculate_gravitational_acceleration(const Entity *entity1, const Entity *entity2,
                                          const Properties *props,
                                          double *accel_x, double *accel_y) {

    const double dx = entity2->position.x - entity1->position.x;
    const double dy = entity2->position.y - entity1->position.y;
    const double dist_squared = dx * dx + dy * dy;
    const double dist = sqrt(dist_squared);

    const double g_force = props->gravity * entity2->mass / dist_squared;

    *accel_x = dx / dist * g_force;
    *accel_y = dy / dist * g_force;

}


/**
 * Calculate simulation frame
 */
void calculate_frame(const Properties *props,
                     const Entity *sun, Entity *earth, Entity *moon,
                     const double t, const double dt) {

    // earth -> sun
    double earth_sun_accel_x;
    double earth_sun_accel_y;
    calculate_gravitational_acceleration(earth, sun, props, &earth_sun_accel_x, &earth_sun_accel_y);

    perform_midpoint_method(dt, earth_sun_accel_x, earth_sun_accel_y,
                            &earth->position.x, &earth->position.y,
                            &earth->velocity.x, &earth->velocity.y);


    // moon -> sun
    double moon_sun_accel_x;
    double moon_sun_accel_y;
    calculate_gravitational_acceleration(moon, sun, props, &moon_sun_accel_x, &moon_sun_accel_y);

    // the moon is orbiting the earth, and we're calculating the absolute acceleration, not local to the earth
    // moon -> earth
    double moon_earth_accel_x;
    double moon_earth_accel_y;
    calculate_gravitational_acceleration(moon, earth, props, &moon_earth_accel_x, &moon_earth_accel_y);

    // global moon acceleration
    const double moon_accel_x = moon_earth_accel_x + moon_sun_accel_x;
    const double moon_accel_y = moon_earth_accel_y + moon_sun_accel_y;

    perform_midpoint_method(dt, moon_accel_x, moon_accel_y,
                            &moon->position.x, &moon->position.y,
                            &moon->velocity.x, &moon->velocity.y);

}


