#pragma once
#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "AnimationData.h"

AnimationComponent::AnimationComponent( SpriteComponent& spriteComponent )
	: m_spriteComponent( spriteComponent )
{ }

void AnimationComponent::setAnimation( const AnimationData* data )
{
	m_animationData = data;
	m_currentFrame = 0;
	m_elapsedTime = 0.0f;

	reset();
}

const AnimationData* AnimationComponent::getAnimation()
{
	return m_animationData;
}

void AnimationComponent::play()
{
	m_state = EState::Playing;
}

void AnimationComponent::pause()
{
	m_state = EState::Paused;
}

void AnimationComponent::stop()
{
	m_state = EState::Stopped;

	reset();
}

void AnimationComponent::onUpdate( float deltaTime )
{
	if ( m_state != EState::Playing || !m_animationData )
	{
		return;
	}

	m_elapsedTime += deltaTime;

	size_t frameIndex = m_currentFrame;

	while ( m_elapsedTime >= m_animationData->frameDuration )
	{
		m_elapsedTime -= m_animationData->frameDuration;
		++frameIndex;

		if ( frameIndex >= m_animationData->frames.size() )
		{
			if ( m_animationData->loop )
			{
				frameIndex = 0;
			}
			else
			{
				frameIndex = m_animationData->frames.size() - 1;
				m_state = EState::Stopped;
			}
		}
	}

	if ( m_currentFrame != frameIndex )
	{
		m_currentFrame = frameIndex;
		m_spriteComponent.setSprite( m_animationData->frames[m_currentFrame] );
	}
}

void AnimationComponent::reset()
{
	m_elapsedTime = 0.0f;
	m_currentFrame = 0;

	if ( !m_animationData->frames.empty() )
	{
		m_spriteComponent.setSprite( m_animationData->frames[m_currentFrame] );
	}
}