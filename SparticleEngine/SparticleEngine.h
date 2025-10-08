#pragma once

#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "EngineConfig.h"
#include "InputManager.h"
#include "GameObject.h"

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

	// GameObject management
	template<typename T, typename... Args>
	T* createObject( Args&&... args )
	{
		auto obj = std::make_unique<T>( this, std::forward<Args>( args )... );
		T* ptr = obj.get();
		m_objects.push_back( std::move( obj ) );
		return ptr;
	}

private:
	SDLState m_sdlState;
	InputManager m_input;
	bool m_isRunning = false;

	std::vector<std::unique_ptr<GameObject>> m_objects;

	GameObject* m_TEMP_player = nullptr;
	SDL_Texture* m_TEMP_spriteSheet;

	void initSDL( const EngineConfig& config );
	void shutdownSDL();

	void loadAssets();
	void unloadAssets();

	void processEvents();
	void update( double deltaTime );
	void render();
};
