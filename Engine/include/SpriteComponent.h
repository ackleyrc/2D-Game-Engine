#pragma once
#include "Component.h"
#include "EngineAPI.h"
#include "Sprite.h"

class SPARTICLE_API SpriteComponent : public Component
{
public:
	SpriteComponent() { }
	~SpriteComponent() { }

	const Sprite& getSprite() const { return m_sprite; }
	void setSprite( const Sprite& sprite ) { m_sprite = sprite; }

private:
	Sprite m_sprite;
};