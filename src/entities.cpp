#include "entities.hpp"

#include <cmath>

#include "world.hpp"

std::list<Character> entities;

Character hero(10, 10, CHAR_HERO);
Character key(605, 305, CHAR_KEY);

inline
int dist(int x0, int y0, int x1, int y1)
{
    return std::abs(x0 - x1) + std::abs(y0 - y1);
}

bool spawn(CharType type, CollisionDetection& colliders, std::random_device& rd)
{
    auto [m, n] = get_size(maze);
    int i = std::uniform_int_distribution<>(0, m/2-1)(rd);
    int j = std::uniform_int_distribution<>(0, n/2-1)(rd);
    if (dist(hero.collider()->get_i(), hero.collider()->get_j(), i*2, j*2) < 5) {
        return false;
    }
    entities.emplace_back(2*gap*i+gap/2, 2*gap*j+gap/2, type);
    colliders.add(entities.back().collider());
    return true;
}

bool key_respawn(std::random_device& rd)
{
    auto [m, n] = get_size(maze);
    int i = std::uniform_int_distribution<>(0, m/2-1)(rd);
    int j = std::uniform_int_distribution<>(0, n/2-1)(rd);
    if (dist(hero.collider()->get_i(), hero.collider()->get_j(), i*2, j*2) < 5) {
        return false;
    }
    key.collider()->teleport(2*gap*i+gap/2, 2*gap*j+gap/2);
    key.revive();
    return true;
}