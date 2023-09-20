#include "SimXApp.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SimXApp::SimXApp(const char* title)
{
	_screenWidth = NULL;
	_screenHeight = NULL;
	_font = NULL;
	_title = title;
	_mouseX = 0;
	_mouseY = 0;
}

SimXApp::~SimXApp()
{
	TTF_CloseFont(_font);

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
			if (TTF_Init() == -1) {
				printf("SDL_ttf not initialized, SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
			else {
				SDL_Surface* icon = IMG_Load("simicon.ico");
				SDL_SetWindowIcon(_window, icon);
				_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
				if (_renderer == NULL) {
					printf("Renderer not created, SDL error: %s\n", SDL_GetError());
					success = false;
				}
				else {
					_font = TTF_OpenFont("consolab.ttf", 20);
					if (_font == NULL) {
						printf("Failed to load consolab.ttf, SDL_ttf error: %s\n", TTF_GetError());
						success = false;
					}
					SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
				}
			}
		}
	}
	return success;
}

void SimXApp::RenderScene() {
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);

	int toolbarHeight = 60;

	// Draw Grid
	SDL_SetRenderDrawColor(_renderer, 0x11, 0x11, 0x11, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < _screenWidth; i += 20) {
		SDL_RenderDrawLine(_renderer, i, toolbarHeight, i, _screenHeight);
	}
	for (int i = toolbarHeight; i < _screenHeight; i += 20) {
		SDL_RenderDrawLine(_renderer, 0, i, _screenWidth, i);
	}

	// Draw simulation tabs
	SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(_renderer, 0, toolbarHeight, _screenWidth, toolbarHeight);

	int initialOffset = 10, tabWidth = 200, tabHeight = 50, cornerRadius = 10;

	SDL_Surface* textSurface = TTF_RenderText_Blended(_font, "Particle", SDL_Color(0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE));
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	int textWidth = textSurface->w;
	int textHeight = textSurface->h;
	SDL_Rect renderQuad = { initialOffset + 10, toolbarHeight - (10 + textHeight), textWidth, textHeight };
	SDL_RenderCopy(_renderer, textTexture, NULL, &renderQuad);

	tabWidth = textWidth + 20;
	tabHeight = textHeight + 20;

	SDL_RenderDrawLine(_renderer, initialOffset, toolbarHeight, initialOffset, toolbarHeight - (tabHeight - cornerRadius));
	SDL_RenderDrawLine(_renderer, tabWidth + initialOffset, toolbarHeight, tabWidth + initialOffset, toolbarHeight - (tabHeight - cornerRadius));
	SDL_RenderDrawLine(_renderer, initialOffset + cornerRadius, toolbarHeight - tabHeight, tabWidth + initialOffset - cornerRadius, toolbarHeight - tabHeight);
	SDL_RenderDrawLine(_renderer, initialOffset, toolbarHeight - (tabHeight - cornerRadius), initialOffset + cornerRadius, toolbarHeight - tabHeight);
	SDL_RenderDrawLine(_renderer, tabWidth + initialOffset - cornerRadius, toolbarHeight - tabHeight, tabWidth + initialOffset, toolbarHeight - (tabHeight - cornerRadius));


	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	

	// Render block placement preview
	SDL_SetRenderDrawColor(_renderer, 0x99, 0x99, 0x99, SDL_ALPHA_OPAQUE);
	SDL_Rect preview = { _mouseX, _mouseY, 50, 50 };
	SDL_RenderDrawRect(_renderer, &preview);


	SDL_RenderPresent(_renderer);
}


void SimXApp::MouseMove(int x, int y, bool mouseDown)
{
	_mouseX = x;
	_mouseY = y;
}
