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
#include "EventSystem.h"
#include "Vector.h"

struct SDLState;

class SPARTICLE_API SparticleEngine
{
public:
	SparticleEngine( const EngineConfig& config );
	~SparticleEngine();

	void setGame( IGame* game ) { m_game = game; }
	void run();

	double getTimeElapsed() { return m_timeElapsed; }
	long getFramesElapsed() { return m_framesElapsed; }

	GameObject* createGameObject();
	void destroyGameObject( GameObject* gameObject );

	InputManager& input() { return m_input; }
	ResourceManager& resources() { return m_resources; }
	EventSystem& events() { return m_eventSystem; }

private:
	EngineConfig m_engineConfig;

	IGame* m_game = nullptr;

	std::unique_ptr<SDLState> m_sdlState;

	InputManager m_input;
	ResourceManager m_resources;
	EventSystem m_eventSystem;

	bool m_isRunning = false;
	double m_timeElapsed = 0.0;
	long m_framesElapsed = 0;

	void initializeGame();
	void shutdownGame();

	void processEvents();
	void update( const double deltaTime );
	void render();

	void processPendingDestruction();

	friend class SpriteComponent;
	void registerSpriteComponent( SpriteComponent* spriteComponent );
	void unregisterSpriteComponent( SpriteComponent* spriteComponent );
	std::map<int, std::vector<SpriteComponent*>> m_spriteLayers;

	std::vector<std::unique_ptr<GameObject>> m_objects;
	std::vector<GameObject*> m_pendingDestroy;
};