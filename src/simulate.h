#ifndef SIMULATE_H
#define SIMULATE_H

/**
 * The constants used in the simulation.
 */
typedef struct {
    double gravity; // N*m^2/kg^2

    double mass_sun; // kg
    double mass_earth; // kg
    double mass_moon; // kg

    double distance_earth_sun; // m
    double distance_earth_moon; // m
} Properties;


/**
 * Vector for 2D coordinates, for double precision.
 */
typedef struct {
    double x;
    double y;
} Vec2d;


/**
 * Representation of an entity in the system.
 */
typedef struct {
    Vec2d position;
    Vec2d velocity;
    Vec2d acceleration;
    double mass;
} Entity;




void perform_midpoint_method(double dt,
                             double accel_x, double accel_y,
                             double *x, double *y,
                             double *dx_dt, double *dy_dt);

void initialize_simulation(Entity *sun, Entity *earth, Entity *moon,
                           const Properties *props);

void calculate_gravitational_acceleration(const Entity *entity1, const Entity *entity2,
                                          const Properties *props,
                                          double *accel_x, double *accel_y);

void calculate_frame(const Properties *props,
                     const Entity *sun, Entity *earth, Entity *moon,
                     double t, double dt) ;


#endif //SIMULATE_H
