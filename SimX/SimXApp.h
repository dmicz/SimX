#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "physics.h"

class SimXApp {
public:
	SimXApp(const char* title);
	~SimXApp();

	void Run();

	bool CreateWindow(int x, int y, int w, int h, Uint32 flags);
private:
	void StartFrame();
	bool HandleEvents();
	void RenderScene();
	void EndFrame();

	const char* _title;
	SDL_Window* _window = NULL;
	SDL_Event _event;
	SDL_Renderer* _renderer = NULL;
	TTF_Font* _font;
	int _screenWidth, _screenHeight;
	int _mouseX, _mouseY;

	Uint32 _fpsStartTicks = 0;
	Uint32 _capStartTicks = 0;
	int _framesElapsed = 0;
	double _avgFramesPerSecond = 0;

	ParticleSimulation _particleSim;
};