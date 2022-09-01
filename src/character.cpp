#include "character.hpp"

#include <array>

Character::Character(int x, int y, CharType type) : type_(type)
{
	sp_circle_ = std::make_shared<Circle>(x, y, 9, max_vel.arr[type], this);
}

