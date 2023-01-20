#pragma once
#include <SDL.h>
#include <stdio.h>
#include "physics.h"

class SimXApp {
public:
	SimXApp(const char* title);
	~SimXApp();

	bool CreateWindow(int x, int y, int w, int h, Uint32 flags);
	void RenderScene();
	void SetPhysicsHandler(PhysicsScene* ps);
	void MouseDown(int x, int y);
private:
	const char* _title;
	SDL_Window* _window = NULL;
	SDL_Renderer* _renderer = NULL;
	int _screenWidth, _screenHeight;

	PhysicsScene* _physicsSimulator;
};