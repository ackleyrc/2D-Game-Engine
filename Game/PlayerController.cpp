#include <cmath>
#include <algorithm>
#include <SparticleEngine.h>
#include "PlayerController.h"
#include "GameConfig.h"
#include "TileMap.h"
#include "ETileType.h"
#include <iostream> // TEMP!

PlayerController::PlayerController(
	AnimationComponent& animationComponent,
	const AnimationData* playerUp,
	const AnimationData* playerDown,
	const AnimationData* playerLeft,
	const AnimationData* playerRight,
	TileMap& tileMap
	) : m_animationComponent( animationComponent ),
		m_playerUp( playerUp ),
		m_playerDown( playerDown ),
		m_playerLeft( playerLeft ),
		m_playerRight( playerRight ),
		m_tileMap( tileMap )
{ }

void PlayerController::onUpdate( float deltaTime )
{
	float x = m_gameObject->x;
	float y = m_gameObject->y;

	const EDirection inputDirection = getInputDirection();

	if ( inputDirection != EDirection::NONE )
	{
		if ( canStartMovingInDirection( x, y, inputDirection, m_tileMap ) )
		{
			m_currentDirection = inputDirection;
		}
	}

	if ( m_currentDirection == EDirection::NONE )
	{
		return;
	}

	constexpr float playerSpeed = 200.0f;
	float travelDistance = playerSpeed * deltaTime;

	int colIndex = static_cast<int>( std::floor( x / GameConfig::TILE_WIDTH ) );
	int rowIndex = static_cast<int>( std::floor( y / GameConfig::TILE_HEIGHT ) );

	while ( m_currentDirection != EDirection::NONE && travelDistance > 0.0f )
	{
		float dx = 0.0f;
		float dy = 0.0f;

		switch ( m_currentDirection )
		{
			case EDirection::UP:    dy = -1.0f;	break;
			case EDirection::DOWN:  dy = 1.0f;	break;
			case EDirection::LEFT:  dx = -1.0f;	break;
			case EDirection::RIGHT: dx = 1.0f;	break;
			default: break;
		}

		if ( !canAdvanceToNextTile( x, y, m_currentDirection, m_tileMap ) )
		{
			m_currentDirection = EDirection::NONE;
			break;
		}

		float distanceToBoundary = 0.0f;

		if ( dx > 0.0f )
		{
			distanceToBoundary = ( colIndex + 1 ) * GameConfig::TILE_WIDTH - x;
		}
		else if ( dx < 0.0f )
		{
			distanceToBoundary = x - colIndex * GameConfig::TILE_WIDTH;
		}
		else if ( dy > 0.0f )
		{
			distanceToBoundary = ( rowIndex + 1 ) * GameConfig::TILE_HEIGHT - y;
		}
		else if ( dy < 0.0f )
		{
			distanceToBoundary = y - rowIndex * GameConfig::TILE_HEIGHT;
		}

		float step = std::min( travelDistance, distanceToBoundary );

		x += dx * step;
		y += dy * step;
		travelDistance -= step;

		bool reachedBoundary = spmath::nearlyEqual( step, distanceToBoundary );

		if ( reachedBoundary )
		{
			rowIndex += static_cast<int>( dy );
			colIndex += static_cast<int>( dx );
		}

		if ( spmath::nearlyEqual( travelDistance, 0.0f ) )
		{
			break;
		}
	}

	m_gameObject->x = x;
	m_gameObject->y = y;


	updateAnimation( m_currentDirection );
}

const PlayerController::EDirection PlayerController::getInputDirection() const
{
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

	return inputDirection;
}

bool PlayerController::canStartMovingInDirection(
	const float x,
	const float y,
	EDirection newDirection,
	const TileMap& tileMap
)
{
	int colIndex = static_cast<int>( x / GameConfig::TILE_WIDTH );
	int rowIndex = static_cast<int>( y / GameConfig::TILE_HEIGHT );

	float xNormalized = std::fmod( x, GameConfig::TILE_WIDTH );
	float yNormalized = std::fmod( y, GameConfig::TILE_HEIGHT );
	if ( xNormalized < 0.0f ) xNormalized += GameConfig::TILE_WIDTH;
	if ( yNormalized < 0.0f ) yNormalized += GameConfig::TILE_HEIGHT;

	switch ( newDirection )
	{
		case EDirection::UP:
			if ( spmath::nearlyEqual( xNormalized, 0.0f ) )
			{
				return isWalkable( tileMap.getTileType( rowIndex - 1, colIndex ) );
			}
			return false;
		case EDirection::DOWN:
			if ( spmath::nearlyEqual( xNormalized, 0.0f ) )
			{
				return isWalkable( tileMap.getTileType( rowIndex + 1, colIndex ) );
			}
			return false;
		case EDirection::LEFT:
			if ( spmath::nearlyEqual( yNormalized, 0.0f ) )
			{
				return isWalkable( tileMap.getTileType( rowIndex, colIndex - 1 ) );
			}
			return false;
		case EDirection::RIGHT:
			if ( spmath::nearlyEqual( yNormalized, 0.0f ) )
			{
				return isWalkable( tileMap.getTileType( rowIndex, colIndex + 1 ) );
			}
			return false;
		default:
			return false;
	}
}

bool PlayerController::canAdvanceToNextTile(
	const float x,
	const float y,
	EDirection currentDirection,
	const TileMap& tileMap
)
{
	int colIndex = static_cast<int>( x / GameConfig::TILE_WIDTH );
	int rowIndex = static_cast<int>( y / GameConfig::TILE_HEIGHT );

	float xNormalized = std::fmod( x, GameConfig::TILE_WIDTH );
	float yNormalized = std::fmod( y, GameConfig::TILE_HEIGHT );
	if ( xNormalized < 0.0f ) xNormalized += GameConfig::TILE_WIDTH;
	if ( yNormalized < 0.0f ) yNormalized += GameConfig::TILE_HEIGHT;

	switch ( currentDirection )
	{
		case EDirection::UP:
			if ( spmath::nearlyEqual( yNormalized, 0.0f ) )
			{
				return isWalkable( tileMap.getTileType( rowIndex - 1, colIndex ) );
			}
			break;
		case EDirection::DOWN:
			if ( spmath::nearlyEqual( yNormalized, 0.0f ) )
			{
				return isWalkable( tileMap.getTileType( rowIndex + 1, colIndex ) );
			}
			break;
		case EDirection::LEFT:
			if ( spmath::nearlyEqual( xNormalized, 0.0f ) )
			{
				return isWalkable( tileMap.getTileType( rowIndex, colIndex - 1 ) );
			}
			break;
		case EDirection::RIGHT:
			if ( spmath::nearlyEqual( xNormalized, 0.0f ) )
			{
				return isWalkable( tileMap.getTileType( rowIndex, colIndex + 1 ) );
			}
			break;
		default:
			return false;
	}

	return true;
}

bool PlayerController::isWalkable( ETileType tileType )
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
}