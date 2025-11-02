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

	void setPositionOffset( float x, float y );

	int getLayer() { return m_layer; }
	void setLayer( int newLayer );

	double getRotationDegrees() { return m_rotationDegrees; }
	void setRotationDegrees( double degrees ) { m_rotationDegrees = degrees; }
	void setRotationPivot( float x, float y );

private:
	friend class SparticleEngine;

	Sprite m_sprite;

	float m_positionOffsetX = 0.0f;
	float m_positionOffsetY = 0.0f;

	int m_layer;

	double m_rotationDegrees = 0.0f;
	float m_rotationPivotX = 0.0f;
	float m_rotationPivotY = 0.0f;
};