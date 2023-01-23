#include "SimXApp.h"
#include <SDL.h>
#include <SDL_image.h>

SimXApp::SimXApp(const char* title)
{
	_screenWidth = NULL;
	_screenHeight = NULL;
	_physicsSimulator = NULL;
	_title = title;
	_mouseX = 0;
	_mouseY = 0;
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
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image not initialized, SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}
		else
		{
			SDL_Surface* icon = IMG_Load("simicon.ico");
			SDL_SetWindowIcon(_window, icon);
			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
			if (_renderer == NULL) {
				printf("Renderer not created, SDL error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
			}
		}
	}
	return success;
}

void SimXApp::RenderScene() {
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);

	//Draw Grid
	SDL_SetRenderDrawColor(_renderer, 0x11, 0x11, 0x11, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < _screenWidth; i += 20) {
		SDL_RenderDrawLine(_renderer, i, 0, i, _physicsSimulator->GetFloorHeight());
	}
	for (int i = 0; i < _physicsSimulator->GetFloorHeight(); i += 20) {
		SDL_RenderDrawLine(_renderer, 0, i, _screenWidth, i);
	}

	// Render block placement preview
	SDL_SetRenderDrawColor(_renderer, 0x99, 0x99, 0x99, SDL_ALPHA_OPAQUE);
	SDL_Rect preview = { _mouseX, _mouseY, 50, 50 };
	SDL_RenderDrawRect(_renderer, &preview);

	// Render Floor
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(_renderer, 0, _physicsSimulator->GetFloorHeight(), _screenWidth, _physicsSimulator->GetFloorHeight());

	// Render blocks
	for (int blockID = 0; blockID < _physicsSimulator->GetNumBlocks(); blockID++) {
		SDL_RenderDrawRect(_renderer, _physicsSimulator->GetBlock(blockID)->GetSDLRect());
	}
	_physicsSimulator->RunForSeconds(1. / 60, 1. / 6000);

	SDL_RenderPresent(_renderer);
}

void SimXApp::SetPhysicsHandler(PhysicsScene* ps)
{
	_physicsSimulator = ps;
}

void SimXApp::MouseMove(int x, int y, bool mouseDown)
{
	_mouseX = x;
	_mouseY = y;
	if (mouseDown) _physicsSimulator->AddBlock(Block(x, y, 50));
}
