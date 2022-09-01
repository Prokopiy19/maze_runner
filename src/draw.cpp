#include "draw.hpp"

#include <array>
#include <iostream>
#include <functional>

#include "SDL_ttf.h"

#include "app.hpp"
#include "char_types.hpp"
#include "entities.hpp"
#include "render.hpp"
#include "texture.hpp"
#include "world.hpp"

namespace {

Texture world_texture, score;

std::array<std::function<void(Renderer)>, SCENE_TOTAL> scenes;

TTF_Font* font = nullptr;

} //namespace


std::array<Texture, CHAR_TOTAL> chars;

void free_textures()
{
    TTF_CloseFont(font);
    font = nullptr;

    world_texture.free();
    score.free();
    for (Texture& texture : chars) {
        texture.free();
    }
}

void build_scenes()
{
    scenes[SCENE_IN_GAME] = [](Renderer renderer)
    {
        renderer.draw(world_texture.texture());

        score.set_text("score: " + std::to_string(hero.score()), font);
        score.render(kWidth/2 - score.width()/2, kHeight-gap);
        renderer.set_draw_color(0xFF, 0x00, 0x00, 0xFF);
        hero.collider()->draw(renderer);
        if (key.is_alive())
            key.collider()->draw(renderer);
        for (auto& entity : entities)
            entity.collider()->draw(renderer);
    };

    scenes[SCENE_PAUSE] = [](Renderer renderer)
    {
        scenes[SCENE_IN_GAME](renderer);

        renderer.set_draw_color(0x00, 0xFF, 0x00, 0xFF);
        renderer.draw_circle(15, 15, 15);
    };

    scenes[SCENE_WIN] = [](Renderer renderer)
    {
        scenes[SCENE_IN_GAME](renderer);

        renderer.set_draw_color(0x00, 0xFF, 0x00, 0xFF);
        renderer.draw_circle(kWidth/2, kHeight/2, 300);
    };

    scenes[SCENE_GAME_OVER] = [](Renderer renderer)
    {
        renderer.set_draw_color(0x00, 0xFF, 0x00, 0xFF);
        score.set_text("Game Over! Score: " + std::to_string(hero.score()), font);
        score.render(kWidth/2 - score.width()/2, kHeight/2 - score.height()/2);
    };

    font = TTF_OpenFont("data/Tuffy_Bold.ttf", 20);
	if(font == nullptr)
	{
        std::cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}

    chars[CHAR_HERO].load("data/hero.png");
    chars[CHAR_MONSTER].load("data/monster.png");
    chars[CHAR_KEY].load("data/key.png");
}

void prepare_scene(Renderer renderer)
{
    renderer.set_draw_color(0x00, 0x00, 0x00, 0x00);
    renderer.clear();

    scenes[current_scene](renderer);
}

void draw_world(const World& world)
{
    auto texture = SDL_CreateTexture(app.renderer().renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, kWidth, kHeight);

    SDL_SetRenderTarget(app.renderer().renderer(), texture);

    app.renderer().set_draw_color(0x00, 0x00, 0x00, 0xFF);

    app.renderer().clear();

    app.renderer().set_draw_color(0xFF, 0xFF, 0xFF, 0x00);

    for (int x = 0; x != kWidth; ++x)
        for (int y = 0; y != kHeight; ++y)
            if (world[x][y]) {
                app.renderer().draw_point(x, y);
            }

    SDL_SetRenderTarget(app.renderer().renderer(), nullptr);

    world_texture.set_texture(texture);
}
