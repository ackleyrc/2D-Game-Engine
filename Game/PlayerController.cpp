#include <cmath>
#include <algorithm>
#include <SparticleEngine.h>
#include "PlayerController.h"
#include "GameConfig.h"
#include "TileMap.h"
#include "ETileType.h"
#include "EDirection.h"

PlayerController::PlayerController(
	SpriteComponent& directionSpriteComponent,
	AnimationComponent& animationComponent,
	const AnimationData* playerUp,
	const AnimationData* playerDown,
	const AnimationData* playerLeft,
	const AnimationData* playerRight,
	TileMap& tileMap
	) : m_directionSpriteComponent( directionSpriteComponent ),
		m_animationComponent( animationComponent ),
		m_playerUp( playerUp ),
		m_playerDown( playerDown ),
		m_playerLeft( playerLeft ),
		m_playerRight( playerRight ),
		m_tileMap( tileMap ),
		m_entityMovement( *this, tileMap ),
		m_lastInputDirection( EDirection::NONE )
{ }

void PlayerController::onUpdate( float deltaTime )
{
	m_entityMovement.update( m_gameObject, deltaTime );

	updateDirectionSprite();

	updateAnimation( m_entityMovement.getCurrentDirection() );
}

EDirection PlayerController::updateDesiredDirection()
{
	const EDirection inputDirection = getInputDirection();

	if ( inputDirection != EDirection::NONE )
	{
		m_lastInputDirection = inputDirection;
	}

	return m_lastInputDirection;
}

const EDirection PlayerController::getInputDirection() const
{
	float horizontalAxis = engine().input().getAxisHorizontal();
	float verticalAxis = engine().input().getAxisVertical();

	EDirection inputDirection = EDirection::NONE;

	if ( verticalAxis > 0.1f )
	{
		inputDirection = EDirection::Up;
	}
	else if ( verticalAxis < -0.1f )
	{
		inputDirection = EDirection::Down;
	}
	else if ( horizontalAxis > 0.1f )
	{
		inputDirection = EDirection::Right;
	}
	else if ( horizontalAxis < -0.1f )
	{
		inputDirection = EDirection::Left;
	}

	return inputDirection;
}

bool PlayerController::isWalkable( const ETileType tileType ) const
{
	switch ( tileType )
	{
		case ETileType::Junction_Pellet:		return true;
		case ETileType::Junction_PowerPellet:	return true;
		case ETileType::Junction_Empty:			return true;
		case ETileType::Path_Pellet:			return true;
		case ETileType::Path_PowerPellet:		return true;
		case ETileType::Path_Empty_Vertical:	return true;
		case ETileType::Path_Empty_Horizontal:	return true;
		default:
			return false;
	}
}

void PlayerController::updateDirectionSprite()
{
	float x = -GameConfig::TILE_WIDTH * 0.5f;
	float y = -GameConfig::TILE_HEIGHT * 0.5f;
	float rotation = 0.0f;

	switch ( m_lastInputDirection )
	{
		case EDirection::Up:
			y -= GameConfig::TILE_HEIGHT * 1.125f;
			break;
		case EDirection::Down:
			y += GameConfig::TILE_HEIGHT * 1.125f;
			rotation = 180.0f;
			break;
		case EDirection::Left:
			x -= GameConfig::TILE_HEIGHT * 1.125f;
			rotation = -90.0f;
			break;
		case EDirection::Right:
			x += GameConfig::TILE_HEIGHT * 1.125f;
			rotation = 90.0f;
			break;
		default:
			return;
	}

	m_directionSpriteComponent.setEnabled( true );
	m_directionSpriteComponent.setPositionOffset( x, y );
	m_directionSpriteComponent.setRotationDegrees( rotation );
}

void PlayerController::updateAnimation( EDirection movementDirection )
{
	if ( movementDirection == EDirection::NONE )
	{
		m_animationComponent.pause();
	}
	else
	{
		const AnimationData* animation = nullptr;

		switch ( movementDirection )
		{
			case EDirection::Up:
				animation = m_playerUp;
				break;
			case EDirection::Left:
				animation = m_playerLeft;
				break;
			case EDirection::Down:
				animation = m_playerDown;
				break;
			case EDirection::Right:
				animation = m_playerRight;
				break;
		}

		if ( animation && animation != m_animationComponent.getAnimation() )
		{
			m_animationComponent.setAnimation( animation );
		}

		m_animationComponent.play();
	}
}