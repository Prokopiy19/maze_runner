#include "texture.hpp"

#include <cassert>
#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "app.hpp"

bool Texture::load(const std::string& path)
{
    free();

    SDL_Surface* loaded_surface = IMG_Load( path.c_str() );
    if(loaded_surface == nullptr)
	{
        std::cout << "Can't load " << path << ": " << IMG_GetError() << std::endl;
        return false;
	}
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0));
    ptexture_ = SDL_CreateTextureFromSurface(app.renderer().renderer(), loaded_surface);
    if(ptexture_ == nullptr)
    {
        std::cout << "Can't create texture from " << path << ": " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loaded_surface);
        return false;
    }
    width_ = loaded_surface->w;
    height_ = loaded_surface->h;

    SDL_FreeSurface(loaded_surface);

    return true;
}

void Texture::free()
{
    if (ptexture_ != nullptr) {
        SDL_DestroyTexture(ptexture_);
        ptexture_ = nullptr;
        width_ = 0;
        height_ = 0;
    }
}

bool Texture::set_text(const std::string& text, TTF_Font* font)
{
    free();

    auto text_surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
    if(text_surface == nullptr) {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << SDL_GetError() << std::endl;
        return false;
    }
    ptexture_ =  SDL_CreateTextureFromSurface(app.renderer().renderer(), text_surface);
    if (ptexture_ == nullptr) {
        std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(text_surface);
        return false;
    }

    width_ = text_surface->w;
    height_ = text_surface->h;

    SDL_FreeSurface(text_surface);

    return true;
}

void Texture::render(int x, int y)
{
    assert((ptexture_));
	SDL_Rect rect = { x, y, width(), height() };
	if (SDL_RenderCopy(app.renderer().renderer(), ptexture_, nullptr, &rect) < 0) {
        std::cout << "can't render " << width() << 'X' << height();
        std::cout << " texture at " << x << ' ' << y;
        std::cout << ". Error: " << SDL_GetError() << std::endl;
    }
}

void Texture::set_texture(SDL_Texture* texture)
{
    ptexture_ = texture;
    SDL_QueryTexture(ptexture_, nullptr, nullptr, &width_, &height_);
}