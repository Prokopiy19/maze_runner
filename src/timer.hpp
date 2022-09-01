#ifndef TIMER_H
#define TIMER_H

#include <cstdint>

#include <SDL.h>

class Timer {
public:
    std::uint64_t watch() const;

    void pause();
    void resume();
    void pause_or_resume();

    bool running() const { return running_; }
private:
    bool running_ = true;
    std::uint64_t start_ = SDL_GetPerformanceCounter();
    std::uint64_t paused_ticks_ = 0;
};

#endif //TIMER_H