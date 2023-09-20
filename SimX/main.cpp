#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>

#include "SimXApp.h"
#include "physics.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc, char* args[]) {
	SimXApp application("SimX");

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
			SDL_Event e;
			
			Uint32 fpsStartTicks = 0;
			Uint32 capStartTicks = 0;
			
			int countedFrames = 0;
			fpsStartTicks = SDL_GetTicks();

			bool quit = false;

			while (!quit) {
				capStartTicks = SDL_GetTicks();

				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) quit = true;
					if (e.type == SDL_MOUSEBUTTONDOWN) {
						int mouseX, mouseY;
						SDL_GetMouseState(&mouseX, &mouseY);
						application.MouseMove(mouseX, mouseY, true);
					}
					if (e.type == SDL_MOUSEMOTION) {
						int mouseX, mouseY;
						SDL_GetMouseState(&mouseX, &mouseY);
						application.MouseMove(mouseX, mouseY, false);
					}
				}

				float avgFPS = countedFrames / ((SDL_GetTicks() - fpsStartTicks) / 1000.f);
				if (avgFPS > 2000000) avgFPS = 0;

				application.RenderScene();

				countedFrames++;
				int frameTicks = (SDL_GetTicks() - capStartTicks);
				if (frameTicks < SCREEN_TICKS_PER_FRAME) {
					SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
				}
			}

			SDL_Quit();
		}
	}


	return 0;
}