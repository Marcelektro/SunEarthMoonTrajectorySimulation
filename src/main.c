#include <stdio.h>
#include "simulate.h"
#include "csv_output.h"

int main() {
    printf("Initializing...\n");

    const Properties props = {
        .gravity = 6.6743e-11, // N*m^2/kg^2
        .mass_sun = 1.989e30, // kg
        .mass_earth = 5.972e24, // kg
        .mass_moon = 7.347e22, // kg
        .distance_earth_sun = 1.5e11, // m
        .distance_earth_moon = 384400000 // m
    };

    const double year_seconds = 365.0 * 24.0 * 60.0 * 60.0; // 365 days as seconds

    const double dt = 160;
    const int steps = (int)(year_seconds / dt);

    FILE* file;
    init_output_file(&file, "output.csv");

    Entity sun = {0};
    Entity earth = {0};
    Entity moon = {0};

    initialize_simulation(&sun, &earth, &moon, &props);

    for (int i = 0; i < steps; i++) {
        const double t = i * dt;

        write_output(file, t,
                     earth.position.x, earth.position.y,
                     moon.position.x, moon.position.y);

        calculate_frame(&props,
                        &sun, &earth, &moon,
                        t, dt);

    }

    close_output_file(file);

    printf("Results written to output file!");

    return 0;
}