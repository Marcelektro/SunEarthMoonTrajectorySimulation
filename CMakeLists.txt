cmake_minimum_required(VERSION 3.30)
project(SunEarthMoonTrajectorySimulation C)

set(CMAKE_C_STANDARD 23)

add_executable(simulate
        src/main.c
)

target_link_libraries(simulate
        m
)
