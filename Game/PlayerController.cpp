#include <cmath>
#include <algorithm>
#include <SparticleEngine.h>
#include "PlayerController.h"
#include "GameConfig.h"

PlayerController::PlayerController(
	AnimationComponent& animationComponent,
	const AnimationData* playerUp,
	const AnimationData* playerDown,
	const AnimationData* playerLeft,
	const AnimationData* playerRight
	) : m_animationComponent( animationComponent ),
		m_playerUp( playerUp ),
		m_playerDown( playerDown ),
		m_playerLeft( playerLeft ),
		m_playerRight( playerRight )
{ }

void PlayerController::onUpdate( float deltaTime )
{
	constexpr float playerSpeed = 200.0f;

	float horizontalAxis = engine().input().getAxisHorizontal();
	float verticalAxis = engine().input().getAxisVertical();

	EDirection inputDirection = EDirection::NONE;

	if ( verticalAxis > 0.1f )
	{
		inputDirection = EDirection::UP;
	}
	else if ( verticalAxis < -0.1f )
	{
		inputDirection = EDirection::DOWN;
	}
	else if ( horizontalAxis > 0.1f )
	{
		inputDirection = EDirection::RIGHT;
	}
	else if ( horizontalAxis < -0.1f )
	{
		inputDirection = EDirection::LEFT;
	}

	if ( inputDirection != EDirection::NONE )
	{
		m_currentDirection = inputDirection;
	}


	float x = m_gameObject->x;
	float y = m_gameObject->y;

	float travelDistance = playerSpeed * deltaTime;

	switch ( m_currentDirection )
	{
		case EDirection::UP:
			y -= travelDistance;
			break;
		case EDirection::LEFT:
			x -= travelDistance;
			break;
		case EDirection::DOWN:
			y += travelDistance;
			break;
		case EDirection::RIGHT:
			x += travelDistance;
			break;
	}

	x = std::clamp(
		x,
		GameConfig::TILE_WIDTH * 0.5f,
		GameConfig::SCREEN_WIDTH - GameConfig::TILE_WIDTH * 2.5f
	);

	y = std::clamp(
		y,
		GameConfig::TILE_HEIGHT * 3.5f,
		GameConfig::SCREEN_HEIGHT - GameConfig::TILE_HEIGHT * 4.5f
	);


	if ( m_gameObject->x != x ||
		m_gameObject->y != y )
	{
		m_gameObject->x = x;
		m_gameObject->y = y;

		const AnimationData* animation = nullptr;

		switch ( m_currentDirection )
		{
			case EDirection::UP:
				animation = m_playerUp;
				break;
			case EDirection::LEFT:
				animation = m_playerLeft;
				break;
			case EDirection::DOWN:
				animation = m_playerDown;
				break;
			case EDirection::RIGHT:
				animation = m_playerRight;
				break;
		}

		if ( animation && animation != m_animationComponent.getAnimation() )
		{
			m_animationComponent.setAnimation( animation );
		}

		m_animationComponent.play();
	}
	else
	{
		m_currentDirection = EDirection::NONE;
		m_animationComponent.pause();
	}
}