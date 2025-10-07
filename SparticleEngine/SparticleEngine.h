#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "EngineConfig.h"
#include "InputManager.h"

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
	InputManager& getInput() { return m_input; }

private:
	SDLState m_sdlState;
	InputManager m_input;
	bool m_isRunning = false;

	float m_TEMP_playerX = 0;
	float m_TEMP_playerY = 0;
	SDL_Texture* m_TEMP_spriteSheet;

	void initSDL( const EngineConfig& config );
	void shutdownSDL();

	void loadAssets();
	void unloadAssets();

	void processEvents();
	void update( double deltaTime );
	void render();
};
