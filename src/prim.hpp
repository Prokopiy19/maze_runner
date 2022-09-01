#ifndef PRIM_H
#define PRIM_H

#include "maze.hpp"
#include <random>
#include "world.hpp"

Maze prim(int w, int h);

void add_loops(std::random_device& rd);

void apply_maze_to_world(const Maze& maze, World& world, int gap);

#endif//PRIM_H
