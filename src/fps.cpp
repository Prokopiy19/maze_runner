#include "fps.hpp"

void FPS::tick()
{
    frames_ += running();
    auto next = timer_.watch();
    delta_ = float(next - current_) / SDL_GetPerformanceFrequency();
    if (delta_ > 1e-30f)
        fps_ = 1.0f / delta_;
    else
        fps_ = 0.0f;
    current_ = next;
}