#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

struct SDLState
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int width = 1600;
	int height = 900;
	int logicalWidth = 640;
	int logicalHeight = 320;
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

	SDL_Texture* m_TEMP_spriteSheet;

	void initSDL();
	void shutdownSDL();

	void loadAssets();
	void unloadAssets();

	void processEvents();
	void update();
	void render();
};
