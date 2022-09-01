#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <SDL_ttf.h>
#include <SDL.h>

class Texture
{
	public:
		Texture() = default; // empty texture
		Texture(const std::string& path) { load(path); }; // load from file

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        bool load(const std::string& path);
        bool set_text(const std::string& text, TTF_Font* font);

		~Texture() { free(); };

		void free();

		void render( int x, int y );

		int width() const { return width_; };
		int height() const { return height_; };

        void set_texture(SDL_Texture* texture);
        SDL_Texture* texture() { return ptexture_; }

	public:
		SDL_Texture* ptexture_ = nullptr;

		int width_ = 0, height_ = 0;
};

#endif