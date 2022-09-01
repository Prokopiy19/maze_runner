#ifndef WORLD_H
#define WORLD_H

#include <cstdint>
#include <array>
#include <bitset>

#include "maze.hpp"
#include "settings.hpp"

using World = std::array<std::bitset<kHeight>, kWidth>;

constexpr int gap = 20;

extern World world;
extern Maze maze;

inline
bool inside(int i, int j)
{
    return (0 <= i) && (i < maze.size())
        && (0 <= j) && (j < maze.front().size());
}

inline
bool can_pass(int i, int j)
{
    return inside(i, j) && maze[i][j] == Cell::kPass;
}

inline
bool can_pass_y (int i, int j)
{
    return can_pass(j, i);
}

std::pair<int, int> get_size(const Maze& maze);

#endif //WORLD_H