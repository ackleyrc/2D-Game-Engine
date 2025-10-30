#pragma once
#include "Component.h"
#include "EngineAPI.h"

class SpriteComponent;
struct AnimationData;

class SPARTICLE_API AnimationComponent : public Component
{
public:
	AnimationComponent( SpriteComponent& spriteComponent );
	~AnimationComponent() { }

	void setAnimation( const AnimationData* data );
	const AnimationData* getAnimation();

	void play();
	void pause();
	void stop();

	void onUpdate( float deltaTime ) override;

private:
	SpriteComponent& m_spriteComponent;
	const AnimationData* m_animationData = nullptr;

	enum class State { Playing, Paused, Stopped };
	State m_state = State::Stopped;

	float m_elapsedTime = 0.0f;
	size_t m_currentFrame = 0;

	void reset();
};