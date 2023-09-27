#include "SimXApp.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SimXApp::SimXApp(const char* title) : m_particleSim(TICKS_PER_SECOND)
{
	m_screenWidth = NULL;
	m_screenHeight = NULL;
	m_font = NULL;
	m_title = title;
	m_mouseX = 0;
	m_mouseY = 0;
	m_event = { };
}

SimXApp::~SimXApp()
{
	TTF_CloseFont(m_font);

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void SimXApp::Run()
{
	m_fpsStartTicks = SDL_GetTicks();

	bool quit = false;

	while (!quit) {
		StartFrame();

		quit = !HandleEvents();

		RenderScene();

		EndFrame();
	}
	while (!quit) {

	}
}

bool SimXApp::CreateWindow(int x, int y, int w, int h, Uint32 flags)
{
	bool success = true;

	m_screenWidth = w;
	m_screenHeight = h;
	m_window = SDL_CreateWindow(m_title, x, y, w, h, flags);
	if (m_window == NULL) {
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
				SDL_SetWindowIcon(m_window, icon);
				m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
				if (m_renderer == NULL) {
					printf("Renderer not created, SDL error: %s\n", SDL_GetError());
					success = false;
				}
				else {
					m_font = TTF_OpenFont("consolab.ttf", 20);
					if (m_font == NULL) {
						printf("Failed to load consolab.ttf, SDL_ttf error: %s\n", TTF_GetError());
						success = false;
					}
					SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
				}
			}
		}
	}
	return success;
}

void SimXApp::StartFrame()
{
	m_capStartTicks = SDL_GetTicks();
}

bool SimXApp::HandleEvents()
{
	while (SDL_PollEvent(&m_event)) {
		if (m_event.type == SDL_QUIT) return false;

		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(&m_mouseX, &m_mouseY);
			Particle particle = { Vector2D{(double)m_mouseX, (double)m_mouseY}, Vector2D{10.0,20.0}, 1 };
			m_particleSim.addParticle(particle);
		}
		if (m_event.type == SDL_MOUSEMOTION) {
			SDL_GetMouseState(&m_mouseX, &m_mouseY);
			if (m_particleSim.numberOfParticles() >= 1) m_particleSim.setParticleVelocity(m_particleSim.numberOfParticles() - 1, Vector2D{ (double) m_mouseX, (double) m_mouseY } - m_particleSim.getParticlePositions()[m_particleSim.numberOfParticles() - 1]);
		}
	}

	m_particleSim.runTick();

	return true;
}



void SimXApp::RenderScene() {
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_renderer);

	int toolbarHeight = 60;

	// Draw Grid
	SDL_SetRenderDrawColor(m_renderer, 0x11, 0x11, 0x11, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < m_screenWidth; i += 20) {
		SDL_RenderDrawLine(m_renderer, i, toolbarHeight, i, m_screenHeight);
	}
	for (int i = toolbarHeight; i < m_screenHeight; i += 20) {
		SDL_RenderDrawLine(m_renderer, 0, i, m_screenWidth, i);
	}

	// Draw simulation tabs
	SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(m_renderer, 0, toolbarHeight, m_screenWidth, toolbarHeight);

	int initialOffset = 10, tabWidth = 200, tabHeight = 50, cornerRadius = 5;

	SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, "Particle", SDL_Color(0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE));
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	int textWidth = textSurface->w;
	int textHeight = textSurface->h;
	int textPadding = 10;
	SDL_Rect renderQuad = { initialOffset + textPadding,
							toolbarHeight - (textPadding + textHeight),
							textWidth, textHeight };
	SDL_RenderCopy(m_renderer, textTexture, NULL, &renderQuad);

	tabWidth = textWidth + 20;
	tabHeight = textHeight + 20;


	SDL_RenderDrawLine(m_renderer, initialOffset, toolbarHeight, initialOffset, toolbarHeight - (tabHeight - cornerRadius));
	SDL_RenderDrawLine(m_renderer, tabWidth + initialOffset, toolbarHeight, tabWidth + initialOffset, toolbarHeight - (tabHeight - cornerRadius));
	SDL_RenderDrawLine(m_renderer, initialOffset + cornerRadius, toolbarHeight - tabHeight, tabWidth + initialOffset - cornerRadius, toolbarHeight - tabHeight);
	SDL_RenderDrawLine(m_renderer, initialOffset, toolbarHeight - (tabHeight - cornerRadius), initialOffset + cornerRadius, toolbarHeight - tabHeight);
	SDL_RenderDrawLine(m_renderer, tabWidth + initialOffset - cornerRadius, toolbarHeight - tabHeight, tabWidth + initialOffset, toolbarHeight - (tabHeight - cornerRadius));


	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	// Simulation
	std::vector<Vector2D> particlePositions = m_particleSim.getParticlePositions();
	for (int i = 0; i < particlePositions.size(); i++) {
		Vector2D particleRenderPoint = SimulationToRenderSpace(particlePositions[i]);
		SDL_RenderDrawPoint(m_renderer, particleRenderPoint.x, particleRenderPoint.y);
	}


	SDL_RenderPresent(m_renderer);
}

void SimXApp::EndFrame()
{
	
	m_avgFramesPerSecond = m_framesElapsed / ((SDL_GetTicks() - m_fpsStartTicks) / 1000.f);
	if (m_avgFramesPerSecond > 2000000) m_avgFramesPerSecond = 0;

	m_framesElapsed++;
	int frameTicks = (SDL_GetTicks() - m_capStartTicks);
	if (frameTicks < 1000 / TICKS_PER_SECOND) {
		SDL_Delay(1000 / TICKS_PER_SECOND - frameTicks);
	}
}

Vector2D SimXApp::SimulationToRenderSpace(Vector2D simulationPoint)
{
	return Vector2D(std::max(0.0, std::min((double)m_screenWidth, simulationPoint.x)),
		std::max(0.0, std::min((double)m_screenHeight, simulationPoint.y)));
}
