#pragma once
#include <SDL.h>

class Texture {
	Texture();
	~Texture();

	void free();
	void render(int x, int y, SDL_Rect* clip = NULL);

private:
	SDL_Texture* _texture;
};