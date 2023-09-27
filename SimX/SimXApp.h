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
	const int TICKS_PER_SECOND = 100;

	void StartFrame();
	bool HandleEvents();
	void RenderScene();
	void EndFrame();

	const char* m_title;
	SDL_Window* m_window = NULL;
	SDL_Event m_event;
	SDL_Renderer* m_renderer = NULL;
	TTF_Font* m_font;
	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;

	Uint32 m_fpsStartTicks = 0;
	Uint32 m_capStartTicks = 0;
	int m_framesElapsed = 0;
	double m_avgFramesPerSecond = 0;

	ParticleSimulation m_particleSim;
};