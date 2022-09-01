#ifndef RANDOM_INT_H
#define RANDOM_INT_H

#include <random>

class RandomInt {
public:
    RandomInt() : e(std::time(0)) {}
    
    //returns a random number between 0 and n-1
    int operator()(int n) { return std::uniform_int_distribution<int>(0, n-1)(e); }
private:
    std::default_random_engine e;
};

#endif //RANDOM_INT_H