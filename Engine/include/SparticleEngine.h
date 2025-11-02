#pragma once
#include <map>
#include <vector>
#include <memory>
#include "EngineAPI.h"
#include "EngineConfig.h"

// Aggregated types
#include "IGame.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Sprite.h"
#include "AnimationData.h"
#include "AnimationComponent.h"
#include "Color.h"
#include "MathUtils.h"

struct SDLState;

class SPARTICLE_API SparticleEngine
{
public:
	SparticleEngine( const EngineConfig& config, IGame* game );
	~SparticleEngine();

	void run();

	GameObject* createGameObject();

	InputManager& input() { return m_input; }
	ResourceManager& resources() { return m_resources; }

private:
	EngineConfig m_engineConfig;

	IGame* m_game;

	std::unique_ptr<SDLState> m_sdlState;

	InputManager m_input;
	ResourceManager m_resources;

	bool m_isRunning = false;

	void processEvents();
	void update( double deltaTime );
	void render();

	friend class SpriteComponent;
	void registerSpriteComponent( SpriteComponent* spriteComponent );
	void unregisterSpriteComponent( SpriteComponent* spriteComponent );
	std::map<int, std::vector<SpriteComponent*>> m_spriteLayers;

	std::vector<std::unique_ptr<GameObject>> m_objects;
};