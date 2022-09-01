#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>

enum class Cell { kWall, kPass };

using Maze = std::vector<std::vector<Cell>>;

#endif