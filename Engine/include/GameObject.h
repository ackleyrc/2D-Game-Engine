#pragma once
#include <string>
#include <memory>
#include "EngineAPI.h"
#include "Sprite.h"

class SparticleEngine;
class ResourceManager;
class InputManager;

class SPARTICLE_API GameObject
{
public:
	GameObject( SparticleEngine* engine );
	virtual ~GameObject() = default;

	GameObject( const GameObject& ) = delete;
	GameObject& operator=( const GameObject& ) = delete;

	// Transform
	float x = 0.0f;
	float y = 0.0f;

	void setSprite( const Sprite& sprite ) { m_sprite = sprite; }

	virtual void onUpdate( float deltaTime );

protected:
	SparticleEngine& engine() const;
	ResourceManager& resources() const;
	InputManager& input() const;

private:
	friend class SparticleEngine;
	SparticleEngine* m_engine = nullptr;
	Sprite m_sprite;
};