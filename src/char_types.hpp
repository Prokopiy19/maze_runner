#ifndef CHAR_TYPES_HPP
#define CHAR_TYPES_HPP

enum CharType { CHAR_HERO, CHAR_KEY, CHAR_MONSTER, CHAR_TOTAL };

struct MAX_VEL {
    constexpr MAX_VEL() : arr() {
        arr[CHAR_HERO] = 100.;
        arr[CHAR_MONSTER] = 90.;
    }
    int arr[CHAR_TOTAL];
};

constexpr auto max_vel = MAX_VEL();

#endif