#pragma once
#include <vector>
#include <memory>
#include "EngineAPI.h"
#include "EngineConfig.h"
#include "IGame.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Sprite.h"

struct SDLState;

class SPARTICLE_API SparticleEngine
{
public:
	SparticleEngine( const EngineConfig& config, IGame* game );
	~SparticleEngine();

	void run();

	InputManager& getInput() { return m_input; }
	ResourceManager& getResources() { return m_resources; }

	// GameObject management
	template<typename T, typename... Args>
	T* createObject( Args&&... args )
	{
		static_assert( std::is_base_of_v<GameObject, T>, "T must derive from GameObject" );
		auto obj = std::make_unique<T>( this, std::forward<Args>( args )... );
		T* ptr = obj.get();
		m_objects.push_back( std::move( obj ) );
		return ptr;
	}

private:
	IGame* m_game;

	std::unique_ptr<SDLState> m_sdlState;

	InputManager m_input;
	ResourceManager m_resources;

	bool m_isRunning = false;

	std::vector<std::unique_ptr<GameObject>> m_objects;

	void processEvents();
	void update( double deltaTime );
	void render();
};