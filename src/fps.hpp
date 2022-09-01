#ifndef FPS_H
#define FPS_H

#include <cstdint>

#include "timer.hpp"

class FPS {
public:
    float delta() const { return delta_; }
    float fps() const { return fps_; }
    float avg_fps() const
        { return float(frames_ * SDL_GetPerformanceFrequency()) / timer_.watch(); }

    void pause() { timer_.pause(); }
    void resume() { timer_.resume(); }
    void pause_or_resume() { timer_.pause_or_resume(); }

    bool running() const { return timer_.running(); }

    void tick();

private:
    Timer timer_;

    std::uint64_t current_ = 0;
    std::uint64_t frames_ = 0;
    float delta_ = 0.0f;
    float fps_ = 0.0f;
};

#endif //FPS_H