#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>

#include "circle.hpp"
#include "char_types.hpp"

class Character {
public:
    Character(int x, int y, CharType type);
    auto collider() { return sp_circle_; }
	
	void kill() { is_alive_ = false; }
    void revive() { is_alive_ = true; }
	
	bool is_alive() const { return is_alive_; }
	CharType type() const { return type_; }

    void increase_score() { ++score_; }
    int score() const { return score_; }

private:
    std::shared_ptr<Circle> sp_circle_;
	CharType type_;
	bool is_alive_ = true;
    int score_ = 0;
};

#endif //CHARACTER_H