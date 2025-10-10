#pragma once
#include <string>
#include <memory>
#include "Sprite.h"

class SparticleEngine;

class GameObject
{
public:
	GameObject( SparticleEngine* engine );
	virtual ~GameObject() = default;

	// Transform
	float x = 0.0f;
	float y = 0.0f;

	void setSprite( const Sprite& sprite ) { m_sprite = sprite; }

	virtual void onUpdate( float deltaTime );

protected:
	friend class SparticleEngine;
	SparticleEngine* m_engine = nullptr;
	Sprite m_sprite;
};