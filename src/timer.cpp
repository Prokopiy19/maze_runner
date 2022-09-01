#include "timer.hpp"

std::uint64_t Timer::watch() const
{
    if (running_)
        return SDL_GetPerformanceCounter() - start_;
    else
        return paused_ticks_;
}

void Timer::pause()
{
    if (running_) {
        running_ = false;
        
        paused_ticks_ = SDL_GetPerformanceCounter() - start_;
        start_ = 0;
    }
}

void Timer::resume()
{
    if (!running_) {
        running_ = true;

        start_ = SDL_GetPerformanceCounter() - paused_ticks_;
        paused_ticks_ = 0;
    }
}

void Timer::pause_or_resume()
{
    if (running_)
        pause();
    else
        resume();
}