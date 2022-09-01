#include "world.hpp"

World world;
Maze maze;

std::pair<int, int> get_size(const Maze& maze)
{
    int x_size = maze.size();
    int y_size = maze.front().size();
    return { x_size, y_size };
}