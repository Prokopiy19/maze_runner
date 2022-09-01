#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <list>

#include "circle.hpp"
#include "char_types.hpp"

bool check_collision(const Circle*, const Circle*);

class CollisionDetection {
public:
    void find_collisions();

    void add(std::shared_ptr<Circle> collider)
        { colliders_.push_back(collider); }

    void move();

private:
    std::list<std::shared_ptr<Circle>> colliders_;
};

#endif //COLLISIONS_H
