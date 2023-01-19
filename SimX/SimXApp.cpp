#include "SimXApp.h"

SimXApp::SimXApp(const char* title)
{
	_title = title;
}

SimXApp::~SimXApp()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

bool SimXApp::CreateWindow(int x, int y, int w, int h, Uint32 flags)
{
	bool success = true;

	_screenWidth = w;
	_screenHeight = h;
	_window = SDL_CreateWindow(_title, x, y, w, h, flags);
	if (_window == NULL) {
		printf("Window not created, SDL error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
		if (_renderer == NULL) {
			printf("Renderer not created, SDL error: %s\n", SDL_GetError());
		}
		else {
			SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
		}
	}
	return success;
}

void SimXApp::RenderScene() {
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);

	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	int boxSize = 50;
	SDL_Rect box = { (_screenWidth - boxSize) / 2, (_screenHeight - boxSize) / 2, boxSize, boxSize };
	SDL_RenderDrawRect(_renderer, &box);

	SDL_RenderPresent(_renderer);
}