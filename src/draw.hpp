#ifndef DRAW_H
#define DRAW_H

#include "char_types.hpp"
#include "render.hpp"
#include "texture.hpp"
#include "world.hpp"

#include <SDL.h>

extern std::array<Texture, CHAR_TOTAL> chars;

void prepare_scene(Renderer renderer);

void draw_world(const World& world);

void build_scenes();

void free_textures();

#endif //DRAW_H