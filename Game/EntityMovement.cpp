#include "EntityMovement.h"
#include <SparticleEngine.h>
#include "GameConfig.h"
#include "EDirection.h"
#include "ETileType.h"
#include "TileMap.h"
#include "IMovementController.h"

EntityMovement::EntityMovement( IMovementController& controller, TileMap& tileMap ) :
	m_controller( controller ),
	m_tileMap( tileMap ),
	m_currentDirection( EDirection::NONE )
{ }

EntityMovement::~EntityMovement() = default;

void EntityMovement::update( GameObject* gameObject, const float deltaTime )
{
	float x = gameObject->x;
	float y = gameObject->y;

	float travelDistance = m_speed * deltaTime;

	int colIndex = static_cast<int>( std::floor( x / GameConfig::TILE_WIDTH ) );
	int rowIndex = static_cast<int>( std::floor( y / GameConfig::TILE_HEIGHT ) );

	EDirection desiredDirection = m_controller.updateDesiredDirection();

	if ( desiredDirection != EDirection::NONE )
	{
		if ( canStartMovingInDirection( x, y, desiredDirection, m_tileMap ) )
		{
			m_currentDirection = desiredDirection;
		}
	}

	while ( m_currentDirection != EDirection::NONE && travelDistance > 0.0f )
	{
		float dx = 0.0f;
		float dy = 0.0f;

		switch ( m_currentDirection )
		{
			case EDirection::Up:    dy = -1.0f;	break;
			case EDirection::Down:  dy = 1.0f;	break;
			case EDirection::Left:  dx = -1.0f;	break;
			case EDirection::Right: dx = 1.0f;	break;
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
			auto desiredDirection = m_controller.updateDesiredDirection();

			if ( desiredDirection != EDirection::NONE )
			{
				if ( canStartMovingInDirection( x, y, desiredDirection, m_tileMap ) )
				{
					m_currentDirection = desiredDirection;

					float dx = 0.0f;
					float dy = 0.0f;

					switch ( m_currentDirection )
					{
						case EDirection::Up:    dy = -1.0f;	break;
						case EDirection::Down:  dy = 1.0f;	break;
						case EDirection::Left:  dx = -1.0f;	break;
						case EDirection::Right: dx = 1.0f;	break;
						default: break;
					}
				}
			}

			rowIndex += static_cast<int>( dy );
			colIndex += static_cast<int>( dx );

			// There are certainly more scalable ways to do this, but for sake of simplicity,
			// we can leverage the known common properties of portals in every level
			if ( m_currentDirection == EDirection::Left )
			{
				if ( spmath::nearlyEqual( x, 0.0f ) )
				{
					x = GameConfig::SCREEN_WIDTH - GameConfig::TILE_WIDTH;
					colIndex = GameConfig::TILE_COLS - 1;
				}
			}
			else if ( m_currentDirection == EDirection::Right )
			{
				if ( spmath::nearlyEqual( x, GameConfig::SCREEN_WIDTH - GameConfig::TILE_WIDTH ) )
				{
					x = 0.0f;
					colIndex = 0;
				}
			}
		}

		if ( spmath::nearlyEqual( travelDistance, 0.0f ) )
		{
			break;
		}
	}

	gameObject->x = x;
	gameObject->y = y;
}

bool EntityMovement::canStartMovingInDirection(
	float x,
	float y,
	EDirection newDirection,
	const TileMap& tileMap
)
{
	int colIndex = static_cast<int>( x / GameConfig::TILE_WIDTH );
	int rowIndex = static_cast<int>( y / GameConfig::TILE_HEIGHT );

	float xOffset = std::fmod( x, GameConfig::TILE_WIDTH );
	float yOffset = std::fmod( y, GameConfig::TILE_HEIGHT );
	if ( xOffset < 0.0f ) xOffset += GameConfig::TILE_WIDTH;
	if ( yOffset < 0.0f ) yOffset += GameConfig::TILE_HEIGHT;

	switch ( newDirection )
	{
		case EDirection::Up:
			if ( spmath::nearlyEqual( xOffset, 0.0f ) )
			{
				return m_controller.isWalkable( tileMap.getTileType( rowIndex - 1, colIndex ) );
			}
			return false;
		case EDirection::Down:
			if ( spmath::nearlyEqual( xOffset, 0.0f ) )
			{
				return m_controller.isWalkable( tileMap.getTileType( rowIndex + 1, colIndex ) );
			}
			return false;
		case EDirection::Left:
			if ( spmath::nearlyEqual( yOffset, 0.0f ) )
			{
				return m_controller.isWalkable( tileMap.getTileType( rowIndex, colIndex - 1 ) );
			}
			return false;
		case EDirection::Right:
			if ( spmath::nearlyEqual( yOffset, 0.0f ) )
			{
				return m_controller.isWalkable( tileMap.getTileType( rowIndex, colIndex + 1 ) );
			}
			return false;
		default:
			return false;
	}
}

bool EntityMovement::canAdvanceToNextTile(
	const float x,
	const float y,
	EDirection currentDirection,
	const TileMap& tileMap
)
{
	int colIndex = static_cast<int>( x / GameConfig::TILE_WIDTH );
	int rowIndex = static_cast<int>( y / GameConfig::TILE_HEIGHT );

	float xOffset = std::fmod( x, GameConfig::TILE_WIDTH );
	float yOffset = std::fmod( y, GameConfig::TILE_HEIGHT );
	if ( xOffset < 0.0f ) xOffset += GameConfig::TILE_WIDTH;
	if ( yOffset < 0.0f ) yOffset += GameConfig::TILE_HEIGHT;

	switch ( currentDirection )
	{
		case EDirection::Up:
			if ( spmath::nearlyEqual( yOffset, 0.0f ) )
			{
				return m_controller.isWalkable( tileMap.getTileType( rowIndex - 1, colIndex ) );
			}
			break;
		case EDirection::Down:
			if ( spmath::nearlyEqual( yOffset, 0.0f ) )
			{
				return m_controller.isWalkable( tileMap.getTileType( rowIndex + 1, colIndex ) );
			}
			break;
		case EDirection::Left:
			if ( spmath::nearlyEqual( xOffset, 0.0f ) )
			{
				return m_controller.isWalkable( tileMap.getTileType( rowIndex, colIndex - 1 ) );
			}
			break;
		case EDirection::Right:
			if ( spmath::nearlyEqual( xOffset, 0.0f ) )
			{
				return m_controller.isWalkable( tileMap.getTileType( rowIndex, colIndex + 1 ) );
			}
			break;
		default:
			return false;
	}

	return true;
}