#include <stdio.h>
#include "simulate.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "gl_trail.h"


/*************\
|* Constants *|
\*************/

#define WINDOW_X        720
#define WINDOW_Y        720
#define WINDOW_TITLE    "SunEarthMoonTrajectorySimulation"

#define POS_SCALE   1e-9 // scale for the positions
#define MOON_EXP    30.0 // scale for moon distance to be visible

#define TRAIL_MAX_POINTS 1000 // max points to keep in the trail

#define UPDATES_PER_TICK    12345 // how many times the update is done per frame
#define TIME_STEP           160.0 // dt


/**
 * Render the scene with the sun, earth, and moon, as well as their trails.
 * Trails are updated here as well, depending on how bodies are rendered (scaling).
 */
void render_scene(const Entity *sun, const Entity *earth, const Entity *moon,
                  Trail *earth_trail, Trail *moon_trail) {
    glClear(GL_COLOR_BUFFER_BIT);

    trail_render(earth_trail);
    trail_render(moon_trail);

    // scaled sun
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // yellow
    glTranslated(sun->position.x * POS_SCALE,
                 sun->position.y * POS_SCALE,
                 0);
    glutSolidSphere(15.0, 30, 30); // sun radius 15
    glPopMatrix();

    // scaled earth
    const Vec2d earth_display = {
        .x = earth->position.x * POS_SCALE,
        .y = earth->position.y * POS_SCALE
    };
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glTranslated(earth_display.x, earth_display.y, 0);
    glutSolidSphere(5.0, 30, 30); // earth radius 5
    glPopMatrix();

    // scaled moon
    const Vec2d moon_display = {
        .x = earth_display.x + (moon->position.x - earth->position.x) * MOON_EXP * POS_SCALE,
        .y = earth_display.y + (moon->position.y - earth->position.y) * MOON_EXP * POS_SCALE
    };

    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f); // gray
    glTranslated(moon_display.x, moon_display.y, 0);
    glutSolidSphere(1.5, 30, 30); // moon radius 1.5
    glPopMatrix();


    trail_update(earth_trail, earth_display.x, earth_display.y);
    trail_update(moon_trail, moon_display.x, moon_display.y);

    glfwSwapBuffers(glfwGetCurrentContext());
}




int main(int argc, char **argv) {

    glutInit(&argc, argv);

    if (!glfwInit())
        return -1;

    printf("Initializing simulation...\n");


    const Properties props = {
        .gravity = 6.6743e-11, // N*m^2/kg^2
        .mass_sun = 1.989e30, // kg
        .mass_earth = 5.972e24, // kg
        .mass_moon = 7.347e22, // kg
        .distance_earth_sun = 1.5e11, // m
        .distance_earth_moon = 384400000 // m
    };


    // bodies
    Entity sun = {0};
    Entity earth = {0};
    Entity moon = {0};

    initialize_simulation(&sun, &earth, &moon, &props);

    // trails
    Trail earth_trail = create_trail((Color){0, 0, 255}, TRAIL_MAX_POINTS);
    Trail moon_trail = create_trail((Color){90, 90, 100}, TRAIL_MAX_POINTS);


    // window
    GLFWwindow *window = glfwCreateWindow(WINDOW_X, WINDOW_Y, WINDOW_TITLE, NULL, NULL);

    if (!window) {
        perror("Error creating GLFW window, exiting...");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); // V-Sync

    const int r = 200;
    glOrtho(-r, r, -r, r, 0, r);


    double prev_time = glfwGetTime();

    // render loop
    while (!glfwWindowShouldClose(window)) {
        const double current_time = glfwGetTime();

        const double time_diff = current_time - prev_time;

        for (int i = 0; i < UPDATES_PER_TICK; ++i) {
            const double dt = TIME_STEP;

            calculate_frame(&props,
                            &sun, &earth, &moon,
                            current_time, time_diff*dt);
        }

        render_scene(&sun, &earth, &moon, &earth_trail, &moon_trail);

        glfwPollEvents();

        prev_time = current_time;
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
