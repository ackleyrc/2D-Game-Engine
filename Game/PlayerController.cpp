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

	Direction inputDirection = Direction::NONE;

	if ( verticalAxis > 0.1f )
	{
		inputDirection = Direction::UP;
	}
	else if ( verticalAxis < -0.1f )
	{
		inputDirection = Direction::DOWN;
	}
	else if ( horizontalAxis > 0.1f )
	{
		inputDirection = Direction::RIGHT;
	}
	else if ( horizontalAxis < -0.1f )
	{
		inputDirection = Direction::LEFT;
	}

	if ( inputDirection != Direction::NONE )
	{
		m_currentDirection = inputDirection;
	}


	float x = m_gameObject->x;
	float y = m_gameObject->y;

	float travelDistance = playerSpeed * deltaTime;

	switch ( m_currentDirection )
	{
		case Direction::UP:
			y -= travelDistance;
			break;
		case Direction::LEFT:
			x -= travelDistance;
			break;
		case Direction::DOWN:
			y += travelDistance;
			break;
		case Direction::RIGHT:
			x += travelDistance;
			break;
	}

	x = std::clamp(
		x,
		GameConfig::TILE_WIDTH * 1.0f,
		GameConfig::SCREEN_WIDTH - GameConfig::TILE_WIDTH * 3.0f
	);

	y = std::clamp(
		y,
		GameConfig::TILE_HEIGHT * 4.0f,
		GameConfig::SCREEN_HEIGHT - GameConfig::TILE_HEIGHT * 5.0f
	);


	if ( m_gameObject->x != x ||
		m_gameObject->y != y )
	{
		m_gameObject->x = x;
		m_gameObject->y = y;

		const AnimationData* animation = nullptr;

		switch ( m_currentDirection )
		{
			case Direction::UP:
				animation = m_playerUp;
				break;
			case Direction::LEFT:
				animation = m_playerLeft;
				break;
			case Direction::DOWN:
				animation = m_playerDown;
				break;
			case Direction::RIGHT:
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
		m_currentDirection = Direction::NONE;
		m_animationComponent.pause();
	}
}