#include <SDL.h>
#include <stdio.h>

#include "SimXApp.h"
#include "physics.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
	SimXApp application("SimX");
	PhysicsScene physics;

	application.SetPhysicsHandler(&physics);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL couldn't initialize, SDL_Error: %s\n", SDL_GetError());
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		if (!application.CreateWindow(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) {
			printf("SDL couldn't create window, SDL_Error: %s\n", SDL_GetError());
		}
		else {
			Block block(10);
			physics.AddEntity(block);
			SDL_Event e;
			bool quit = false;
			while (!quit) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) quit = true;
				}
				application.RenderScene();
			}

			SDL_Quit();
		}
	}


	return 0;
}