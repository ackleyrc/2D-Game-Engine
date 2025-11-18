#include "GhostController.h"
#include <limits>
#include <SparticleEngine.h>
#include "TileMap.h"
#include "ETileType.h"
#include "EDirection.h"
#include "EChaseStrategy.h"
#include "PlayerController.h"
#include "IMovementController.h"

GhostController::GhostController(
	EChaseStrategy chaseStrategy,
	SpriteComponent& spriteComponent,
	TileMap& tileMap,
	PlayerController& playerController
) : m_chaseStrategy( chaseStrategy ),
	m_spriteComponent( spriteComponent ),
	m_tileMap( tileMap ),
	m_playerController( playerController ),
	m_entityMovement( *this, tileMap )
{ }

GhostController::~GhostController() = default;

void GhostController::onAdd()
{
	m_entityMovement.setSpeed( 150.0f );
}

void GhostController::onUpdate( const float deltaTime )
{
	m_entityMovement.update( m_gameObject, deltaTime );
}

EDirection GhostController::updateDesiredDirection( float x, float y )
{
	Vector2f currentPosition = Vector2f( x, y );
	int currentColIndex = m_tileMap.getTileColIndex( x );
	int currentRowIndex = m_tileMap.getTileRowIndex( y );

	auto currentDirection = m_entityMovement.getCurrentDirection();
	auto backtrackDirection = DirectionUtils::getOpposite( currentDirection );

	if ( currentDirection != EDirection::NONE )
	{
		ETileType tileType = m_tileMap.getTileTypeForPosition( currentPosition );

		if ( tileType != ETileType::Junction_Empty &&
			tileType != ETileType::Junction_Pellet &&
			tileType != ETileType::Junction_PowerPellet )
		{
			// Continue on non-junction paths
			return currentDirection;
		}
	}

	Vector2f goalPosition = getGoalPosition();
	EDirection preferredDirection = EDirection::NONE;
	float bestDistanceSqrToGoal = std::numeric_limits<float>::max();

	for ( const auto direction : DirectionUtils::directions )
	{
		if ( direction == currentDirection )
		{
			if ( !m_entityMovement.canAdvanceToNextTile( x, y, direction, m_tileMap ) )
			{
				continue;
			}
		}
		else
		{
			if ( !m_entityMovement.canStartMovingInDirection( x, y, direction, m_tileMap ) )
			{
				continue;
			}
		}

		if ( direction == backtrackDirection )
		{
			continue;
		}

		Vector2f toPosition = m_tileMap.getTilePositionFrom( currentRowIndex, currentColIndex, direction );
		float distanceSqr = ( toPosition - goalPosition ).lengthSqr();

		if ( bestDistanceSqrToGoal > distanceSqr ) {
			bestDistanceSqrToGoal = distanceSqr;
			preferredDirection = direction;
		}
	}

	return preferredDirection != EDirection::NONE ? preferredDirection : backtrackDirection;
}

bool GhostController::isWalkable( const ETileType tileType ) const
{
	switch ( tileType )
	{
		case ETileType::Junction_Pellet:
		case ETileType::Junction_PowerPellet:
		case ETileType::Junction_Empty:
		case ETileType::Path_Pellet:
		case ETileType::Path_PowerPellet:
		case ETileType::Path_Empty_Vertical:
		case ETileType::Path_Empty_Horizontal:
		case ETileType::GhostHomeGate:			
			return true;
		default:
			return false;
	}
}

Vector2f GhostController::getGoalPosition() const
{
	switch ( m_chaseStrategy ) 
	{
		case EChaseStrategy::Aggressive:
		{
			auto playerObj = m_playerController.getGameObject();
			return Vector2f( playerObj->x, playerObj->y );
		}
		case EChaseStrategy::Cunning:
		{
			auto playerObj = m_playerController.getGameObject();
			auto playerCol = m_tileMap.getTileRowIndex( playerObj->x );
			auto playerRow = m_tileMap.getTileRowIndex( playerObj->y );
			auto playerDirection = m_playerController.getCurrentDirection();
			auto oneTileAhead = m_tileMap.getTilePositionFrom( playerRow, playerCol, playerDirection );
			auto playerPosition = Vector2f( playerObj->x, playerObj->y );
			auto playerForward = oneTileAhead - playerPosition;
			return playerPosition + playerForward * 4.0f;
		}
		case EChaseStrategy::Whimsical:	// TODO
		case EChaseStrategy::Timid:		// TODO
		default:
			return Vector2f( 0.0f, 0.0f );
	}
}