cmake_minimum_required(VERSION 3.30)
project(SunEarthMoonTrajectorySimulation C)

set(CMAKE_C_STANDARD 23)

add_executable(simulate
        src/main.c
        src/simulate.c src/simulate.h
        src/csv_output.c src/csv_output.h
)

target_link_libraries(simulate
        m
)


add_executable(visualize
        src/main_realtime.c
        src/simulate.c src/simulate.h
        src/gl_trail.c src/gl_trail.h
)

target_link_libraries(visualize
        m
        GL glut glfw
)

