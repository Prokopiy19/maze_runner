cmake_minimum_required(VERSION 3.27)
project("Maze Runner")

# 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

find_package(SDL2_ttf REQUIRED)

find_package(SDL2_image REQUIRED)

# 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

set(SRCS
    src/main.cpp
    src/prim.cpp
    src/render.cpp
    src/texture.cpp
    src/timer.cpp
    src/world.cpp
    src/action.cpp
    src/ai.cpp
    src/app.cpp
    src/character.cpp
    src/circle.cpp
    src/collider.cpp
    src/collisions.cpp
    src/draw.cpp
    src/entities.cpp
    src/fps.cpp
    src/input.cpp
)
add_executable(maze_runner WIN32 ${SRCS})

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(maze_runner PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(maze_runner PRIVATE SDL2::SDL2)

target_link_libraries(maze_runner PRIVATE SDL2_ttf::SDL2_ttf)

target_link_libraries(maze_runner PRIVATE SDL2_image::SDL2_image)