#pragma once
#include "Component.h"
#include "Sprite.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent() { }
	~SpriteComponent() { }

	const Sprite& getSprite() const { return m_sprite; }
	void setSprite( const Sprite& sprite ) { m_sprite = sprite; }

private:
	Sprite m_sprite;
};