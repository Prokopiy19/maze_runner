#ifndef APP_H
#define APP_H

#include <algorithm>
#include <optional>
#include <random>
#include <string>

#include <SDL.h>

#include "fps.hpp"
#include "render.hpp"

enum SCENES { SCENE_IN_GAME, SCENE_PAUSE, SCENE_UPGRADE, SCENE_WIN, SCENE_GAME_OVER, SCENE_TOTAL };

extern int current_scene;

struct App {
public:
    App();

    ~App() { close(); }

    void Quit() { running_ = false; }

    bool running() const { return running_; }
    int width() const { return width_; }
    int height() const { return height_; }
    Renderer& renderer() { return renderer_; }

    auto delta() const { return std::min(opt_fps_->delta(), 0.05f); }
    void tick() { opt_fps_->tick(); }
    float fps() const { return opt_fps_->fps(); }
    float avg_fps() const { return opt_fps_->avg_fps(); }

    void pause();
    void resume();
    void pause_or_resume();



private:

    void close();

    SDL_Window *ptr_window_ = nullptr;

    int width_ = 0;
    int height_ = 0;

    bool running_ = false;

    Renderer renderer_;

    std::optional<FPS> opt_fps_;

    int prev_scene_;
};

extern App app;

#endif //APP_H
