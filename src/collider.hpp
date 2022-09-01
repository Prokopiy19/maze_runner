#ifndef GEOMETRIC_OBJECT_H
#define GEOMETRIC_OBJECT_H

#include <utility>

#include "render.hpp"
#include "app.hpp"
#include "world.hpp"

class Character;

class Collider {
public:
    enum AiState { MOV_R, MOV_U, MOV_L, MOV_D, STILL };
    enum Move { X, Y };

    virtual ~Collider() = 0;

    Collider(float x, float y, float max_vel, Character *ch) :
        x_(x), y_(y), max_vel_(max_vel), owner_(ch) {
            i_ = get_i();
            j_ = get_j();
        }

    void move();

    float x() const { return x_; }
    float y() const { return y_; }

    void set_vel_x(float vx) { vel_x_ = vx; }
    void set_vel_y(float vy) { vel_y_ = vy; }

    AiState ai_state() const { return ai_state_; }
    void set_ai_state(AiState state);
    AiState prev_state() const { return prev_state_; }

    void set_dest(int di, int dj) { di_ = di; dj_ = dj; }
    // std::pair<int, int> dest() { return { di_, dj_ }; }
    bool pass_dest() const;

    virtual void draw(Renderer&) = 0;
	
	Character* owner() const { return owner_; }

    int get_i() const { return std::round((x_ - gap/2.0)/gap); };
    int get_j() const { return std::round((y_ - gap/2.0)/gap); };

    // teleport: use only on key or other stationary colliders
    void teleport(int x, int y) { x_ = x; y_ = y; }

protected:
    int axis_ = X;
    float max_vel_ = 0.;
    float x_ = 0, y_ = 0;
    float angle_ = 0.0;
    float vel_x_ = 0, vel_y_ = 0; // from 0 to 1
    int i_, j_;
    int di_, dj_;
    AiState ai_state_ = STILL, prev_state_ = STILL;
    static void move_x(float& x, float& y, float vel_x, float vel_y, int& i, int& j,
                      int& axis, float max_vel, bool func(int, int));

	Character* owner_;
};

inline
int sqr_dist(const Collider& lhs, const Collider& rhs)
{
	return (lhs.x() - rhs.x())*(lhs.x() - rhs.x()) +
	       (lhs.y() - rhs.y())*(lhs.y() - rhs.y());
}

#endif //GEOMETRIC_OBJECT_H