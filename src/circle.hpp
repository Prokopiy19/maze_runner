#ifndef CIRCLE_H
#define CIRCLE_H

#include "collider.hpp"

class Circle : public Collider {
public:
    Circle(int x, int y, int r, float max_vel, Character *ch) : Collider(x, y, max_vel, ch), r_(r) {}

    int r() const { return r_; }

    virtual void draw(Renderer&) override;
private:
    int r_;
};

#endif //CIRCLE_H