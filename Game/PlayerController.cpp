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

	float x = m_gameObject->x;
	float y = m_gameObject->y;

	if ( abs(horizontalAxis) > 0.1f )
	{
		x += ( horizontalAxis * playerSpeed * deltaTime );

		x = std::clamp( 
			x, 
			GameConfig::TILE_WIDTH * 1.0f, 
			GameConfig::SCREEN_WIDTH - GameConfig::TILE_WIDTH * 3.0f 
		);

		if ( m_gameObject->x != x )
		{
			m_gameObject->x = x;

			if ( horizontalAxis < 0.0f )
			{
				if ( m_animationComponent.getAnimation() != m_playerLeft )
				{
					m_animationComponent.setAnimation( m_playerLeft );
				}
			}
			else
			{
				if ( m_animationComponent.getAnimation() != m_playerRight )
				{
					m_animationComponent.setAnimation( m_playerRight );
				}
			}

			m_animationComponent.play();
		}
		else
		{
			m_animationComponent.pause();
		}
	}
	else if ( abs(verticalAxis) > 0.1f )
	{
		y -= ( verticalAxis * playerSpeed * deltaTime );

		y = std::clamp( 
			y, 
			GameConfig::TILE_HEIGHT * 4.0f,
			GameConfig::SCREEN_HEIGHT - GameConfig::TILE_HEIGHT * 5.0f 
		);

		if ( m_gameObject->y != y )
		{
			m_gameObject->y = y;

			if ( verticalAxis > 0.0f )
			{
				if ( m_animationComponent.getAnimation() != m_playerUp )
				{
					m_animationComponent.setAnimation( m_playerUp );
				}
			}
			else
			{
				if ( m_animationComponent.getAnimation() != m_playerDown )
				{
					m_animationComponent.setAnimation( m_playerDown );
				}
			}

			m_animationComponent.play();
		}
		else
		{
			m_animationComponent.pause();
		}
	}
	else
	{
		m_animationComponent.pause();
	}
}