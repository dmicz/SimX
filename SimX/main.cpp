#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>

#include "SimXApp.h"
#include "physics.h"


int main(int argc, char* args[]) {
	SimXApp application("SimX");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL couldn't initialize, SDL_Error: %s\n", SDL_GetError());
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		if (!application.CreateWindow(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN)) {
			printf("SDL couldn't create window, SDL_Error: %s\n", SDL_GetError());
		}
		else {
			application.Run();

			SDL_Quit();
		}
	}


	return 0;
}