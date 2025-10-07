#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "EngineConfig.h"

struct SDLState
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int width = 1600;
	int height = 900;
};

class SparticleEngine 
{
public:
	SparticleEngine(const EngineConfig& config);
	~SparticleEngine();

	void run();

private:
	SDLState m_sdlState;
	bool m_isRunning = false;

	SDL_Texture* m_TEMP_spriteSheet;

	void initSDL( const EngineConfig& config );
	void shutdownSDL();

	void loadAssets();
	void unloadAssets();

	void processEvents();
	void update();
	void render();
};
