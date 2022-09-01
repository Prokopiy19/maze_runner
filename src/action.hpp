#ifndef ACTION_H
#define ACTION_H

#include <array>
#include <functional>

#include "character.hpp"

class CollisionAction {
public:
    CollisionAction();

    void operator()(Character *ptr_char1, Character *ptr_char2)
    {
        if (table_[ptr_char1->type()*CHAR_TOTAL + ptr_char2->type()])
            table_[ptr_char1->type()*CHAR_TOTAL + ptr_char2->type()](ptr_char1, ptr_char2);
        else if (table_[ptr_char2->type()*CHAR_TOTAL + ptr_char1->type()])
            table_[ptr_char2->type()*CHAR_TOTAL + ptr_char1->type()](ptr_char2, ptr_char1);
    }
	
private:
    std::array<std::function<void(Character *,
                                Character *)>,
        CHAR_TOTAL*CHAR_TOTAL> table_;
};

#endif //ACTION_H