#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>

#include <iostream>

// SDL renderer wrapper
class Renderer {
public:
    Renderer() = default;
    Renderer(SDL_Renderer *p_render) : ptr_renderer_(p_render) {}

    void clear() const { SDL_RenderClear(ptr_renderer_); }
    void draw_point(int x, int y) const { SDL_RenderDrawPoint(ptr_renderer_, x, y); }
    void present() const { SDL_RenderPresent(ptr_renderer_); }
    void set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
        { SDL_SetRenderDrawColor(ptr_renderer_, r, g, b, a); }

    void draw_ring(int cx, int cy, int rInner, int rOuter) const;
    void draw_circle(int cx, int cy, int r) const;
    void fill_rectangle(int x, int y, int w, int h) const
    {
        SDL_Rect rect = {x, y, w, h};
        SDL_RenderFillRect(ptr_renderer_, &rect);
    }

    void draw(SDL_Texture* texture) const
        { if (SDL_RenderCopy(ptr_renderer_, texture, nullptr, nullptr) < 0) std::cout << SDL_GetError() << std::endl; }

    void set_renderer(SDL_Renderer *p_render) { ptr_renderer_ = p_render; }
    SDL_Renderer *renderer() const { return ptr_renderer_; }
private:
    SDL_Renderer *ptr_renderer_ = nullptr;
};

#endif //RENDER_H
