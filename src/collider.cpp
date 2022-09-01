#include "collider.hpp"

#include <algorithm>
#include <cmath>

#include "maze.hpp"
#include "world.hpp"

#include <iostream> //debug

Collider::~Collider() {}

void Collider::move_x(float& x, float& y, float vel_x, float vel_y, int& i, int& j,
                      int& axis, float max_vel, bool func(int, int))
{
    int ii = std::round((x - gap/2.0)/gap); // don't use get_i here
    i = ii;
    float xx = gap/2.0f + ii * gap;
    float sign; // sign = 1 means collider is on the right side, 0 - on the left side
    if (xx < x)
        sign = -1.0f;
    else
        sign = 1.0f;
    int trying_to_rotate = (vel_y > 0 && func(ii, j + 1))
                        - (vel_y < 0 && func(ii, j - 1));
    
    if (sign * vel_x >= 0 && trying_to_rotate) {
            vel_x += sign * fabs(vel_y);
    }
    vel_x = std::min(1.0f, vel_x);
    vel_x = std::max(-1.0f, vel_x);
    constexpr float EPS = 1e-9f;
    bool equal = fabs(x - xx) < EPS;
    x += app.delta() * max_vel * vel_x;
    if (equal || sign * (xx - x) < 0) {
        if (trying_to_rotate) {
            axis = 1 - axis;
            y += trying_to_rotate * fabs(xx - x);
            x = xx;
            i = ii;
        }
        if (!func(ii + (2*(x - xx > 0) - 1), j)) {
            x = xx;
        }
    }
}

void Collider::move()
{
    vel_x_ = std::min(1.0f, vel_x_);
    vel_x_ = std::max(-1.0f, vel_x_);
    vel_y_ = std::min(1.0f, vel_y_);
    vel_y_ = std::max(-1.0f, vel_y_);
    if (axis_ == X) {
        move_x(x_, y_, vel_x_, vel_y_, i_, j_, axis_, max_vel_, can_pass);
    }
    else {
        move_x(y_, x_, vel_y_, vel_x_, j_, i_, axis_, max_vel_, can_pass_y);
    }
    x_ = std::max(gap/2.f, x_);
    x_ = std::min(kWidth - gap/2.f, x_);
    y_ = std::max(gap/2.f, y_);
    y_ = std::min(kHeight - gap/2.f, y_);
}

void Collider::set_ai_state(AiState state)
{
    if (ai_state_ != STILL)
        prev_state_ = ai_state_;
    ai_state_ = state;
}

bool Collider::pass_dest() const
{
    float dx = gap/2.0 + di_ * gap;
    float dy = gap/2.0 + dj_ * gap;
    constexpr float EPS = 1e-3f;
    // std::cout << (std::fabs(x_ - dx) + std::fabs(y_ - dy)) << std::endl;
    return (std::fabs(x_ - dx) + std::fabs(y_ - dy)) < EPS
         || (dx - x_) * vel_x_ < 0 || (dy - y_) * vel_y_ < 0;
}