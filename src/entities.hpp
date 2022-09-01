#ifndef ENTITIES_H
#define ENTITIES_H

#include "character.hpp"
#include "collisions.hpp"

#include <list>
#include <random>

extern Character hero;

extern Character key;

extern std::list<Character> entities;

bool spawn(CharType type, CollisionDetection& colliders, std::random_device& rd);

bool key_respawn(std::random_device& rd);

#endif //ENTITIES_H