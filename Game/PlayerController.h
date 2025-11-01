#pragma once
#include <Component.h>

class AnimationComponent;
struct AnimationData;

class PlayerController : public Component
{
public:
	PlayerController(
		AnimationComponent& animationComponent,
		const AnimationData* playerUp,
		const AnimationData* playerDown,
		const AnimationData* playerLeft,
		const AnimationData* playerRight
	);

	~PlayerController() { }

	void onUpdate( float deltaTime ) override;

private:
	AnimationComponent& m_animationComponent;
	const AnimationData* m_playerUp;
	const AnimationData* m_playerDown;
	const AnimationData* m_playerLeft;
	const AnimationData* m_playerRight;

	enum class EDirection { NONE, UP, LEFT, DOWN, RIGHT };
	EDirection m_currentDirection = EDirection::NONE;
};