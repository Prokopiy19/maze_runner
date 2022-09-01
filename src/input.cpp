#include "input.hpp"

#include <SDL.h>

#include "app.hpp"
#include "entities.hpp"

void handle_events()
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                app.Quit();
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_p:
                        app.pause_or_resume();
                        break;
                }
                break;
        }
    }

    constexpr int INF = 1'000'000;

    static auto state = SDL_GetKeyboardState(nullptr);
    hero.collider()->set_vel_x(INF*(state[SDL_SCANCODE_D] - state[SDL_SCANCODE_A]));
    hero.collider()->set_vel_y(INF*(-state[SDL_SCANCODE_W] + state[SDL_SCANCODE_S]));
}
