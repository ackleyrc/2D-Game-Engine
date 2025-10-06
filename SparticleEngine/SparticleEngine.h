#pragma once

#include <SDL3/SDL.h>

struct SDLState
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};

class SparticleEngine 
{
public:
	SparticleEngine();
	~SparticleEngine();

	void run();

private:
	SDLState m_sdlState;
	bool m_isRunning = false;

	void initSDL();
	void shutdownSDL();

	void processEvents();
	void update();
	void render();
};
