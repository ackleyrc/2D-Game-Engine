#pragma once
#include "SpriteComponent.h"
#include "SparticleEngine.h"

void SpriteComponent::onAdd()
{
	auto& engine = this->engine();
	engine.registerSpriteComponent( this );
}

SpriteComponent::~SpriteComponent()
{
	auto& engine = this->engine();
	engine.unregisterSpriteComponent( this );
}

void SpriteComponent::setLayer( int newLayer )
{
	if ( newLayer == m_layer )
	{
		return;
	}

	auto& engine = this->engine();
	engine.unregisterSpriteComponent( this );
	
	m_layer = newLayer;
	engine.registerSpriteComponent( this );
}

void SpriteComponent::setRotationPivot( float x, float y )
{
	m_rotationPivotX = x;
	m_rotationPivotY = y;
}

void SpriteComponent::setPositionOffset( float x, float y )
{
	m_positionOffsetX = x;
	m_positionOffsetY = y;
}