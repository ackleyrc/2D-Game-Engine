#pragma once
#include "Component.h"
#include "EngineAPI.h"
#include "Sprite.h"

class SparticleEngine;

class SPARTICLE_API SpriteComponent : public Component
{
public:
	SpriteComponent( int layer = 0 ) { m_layer = layer; }
	~SpriteComponent();

	void onAdd() override;

	const Sprite& getSprite() const { return m_sprite; }
	void setSprite( const Sprite& sprite ) { m_sprite = sprite; }

	int getLayer() { return m_layer; }
	void setLayer( int newLayer );

private:
	friend class SparticleEngine;

	Sprite m_sprite;
	int m_layer;
};