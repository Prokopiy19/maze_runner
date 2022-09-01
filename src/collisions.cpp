#include "collisions.hpp"

#include <iostream>

#include "action.hpp"

namespace {

CollisionAction collision_action;

}//namespace

bool check_collision(const Circle& lhs, const Circle& rhs)
{
    bool collision = false;
    if (sqr_dist(lhs, rhs) <= (lhs.r() + rhs.r())*(lhs.r() + rhs.r())) {
        collision = true;
        collision_action(lhs.owner(), rhs.owner());
    }
    return collision;
}

void CollisionDetection::move()
{
    for (auto& collider : colliders_) {
        collider->move();
    }
}

void CollisionDetection::find_collisions()
{
    for (auto i = colliders_.begin(); i != colliders_.end(); ++i) {
        auto j = i;
        ++j;
        for (/*null*/; j != colliders_.end(); ++j) {
            check_collision(**i, **j);
        }
    }
}