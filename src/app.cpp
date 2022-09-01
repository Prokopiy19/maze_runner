#include "app.hpp"

#include <cmath>

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "settings.hpp"

App app;

int current_scene = SCENE_IN_GAME;

App::App()
{
    width_ = kWidth;
    height_ = kHeight;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        close();
        throw;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    ptr_window_ = SDL_CreateWindow(kWindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_SHOWN);
    if (!ptr_window_) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        close();
        throw;
    }

    auto ptr_renderer = SDL_CreateRenderer(ptr_window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ptr_renderer) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        close();
        throw;
    }

    int img_flags = IMG_INIT_PNG;
    if(!(IMG_Init(img_flags) & img_flags))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        close();
        throw;
    }

    if( TTF_Init() == -1 )
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        close();
        throw;
    }

    renderer().set_renderer(ptr_renderer);

    opt_fps_.emplace();

    running_ = true;
    std::cout << "SDL initialized" << std::endl;
}

void App::close()
{
    running_ = false;

    SDL_DestroyRenderer(renderer().renderer());
    renderer().set_renderer(nullptr);

    SDL_DestroyWindow(ptr_window_);
    ptr_window_ = nullptr;

    TTF_Quit();
	IMG_Quit();
    SDL_Quit();

    std::cout << "SDL shutdown" << std::endl;
}

void App::pause()
{
    opt_fps_->pause();
    prev_scene_ = current_scene;
    current_scene = SCENE_PAUSE;
}

void App::resume()
{
    opt_fps_->resume();
    current_scene = prev_scene_;
}

void App::pause_or_resume()
{
    if (opt_fps_->running())
        pause();
    else
        resume();
}
