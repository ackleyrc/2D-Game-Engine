#include "GhostController.h"
#include <limits>
#include <SparticleEngine.h>
#include "GameConfig.h"
#include "TileMap.h"
#include "ETileType.h"
#include "EDirection.h"
#include "EChaseStrategy.h"
#include "PlayerController.h"
#include "AIBlackboard.h"
#include "IMovementController.h"

GhostController::GhostController(
	EChaseStrategy chaseStrategy,
	SpriteComponent& spriteComponent,
	AIBlackboard& aiBlackboard
) : m_chaseStrategy( chaseStrategy ),
	m_spriteComponent( spriteComponent ),
	m_aiBlackboard( aiBlackboard ),
	m_entityMovement( *this, m_aiBlackboard.getTileMap() )
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
	auto& tileMap = m_aiBlackboard.getTileMap();

	Vector2f currentPosition = Vector2f( x, y );
	int currentColIndex = tileMap.getTileColIndex( x );
	int currentRowIndex = tileMap.getTileRowIndex( y );

	auto currentDirection = m_entityMovement.getCurrentDirection();
	auto backtrackDirection = DirectionUtils::getOpposite( currentDirection );

	Vector2f goalPosition = getGoalPosition();

	Vector2f halfTile = Vector2f( GameConfig::TILE_WIDTH, GameConfig::TILE_HEIGHT ) * 0.5f;
	m_gameObject->debugDraw().drawLine(
		m_gameObject->position + halfTile,
		goalPosition + halfTile,
		Color( 1.0f, 0.0f, 0.0f, 1.0f )
	);

	if ( currentDirection != EDirection::NONE )
	{
		ETileType tileType = tileMap.getTileTypeForPosition( currentPosition );

		if ( tileType != ETileType::Junction_Empty &&
			tileType != ETileType::Junction_Pellet &&
			tileType != ETileType::Junction_PowerPellet )
		{
			// Continue on non-junction paths
			return currentDirection;
		}
	}

	EDirection preferredDirection = EDirection::NONE;
	float bestDistanceSqrToGoal = std::numeric_limits<float>::max();

	for ( const auto direction : DirectionUtils::directions )
	{
		if ( direction == currentDirection )
		{
			if ( !m_entityMovement.canAdvanceToNextTile( x, y, direction, tileMap ) )
			{
				continue;
			}
		}
		else
		{
			if ( !m_entityMovement.canStartMovingInDirection( x, y, direction, tileMap ) )
			{
				continue;
			}
		}

		if ( direction == backtrackDirection )
		{
			continue;
		}

		Vector2f toPosition = tileMap.getTilePositionFrom( currentRowIndex, currentColIndex, direction );
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
			return m_aiBlackboard.getPlayerPosition();
		}
		case EChaseStrategy::Cunning:
		{
			auto& tileMap = m_aiBlackboard.getTileMap();
			auto playerPosition = m_aiBlackboard.getPlayerPosition();
			auto playerCol = tileMap.getTileRowIndex( playerPosition.x );
			auto playerRow = tileMap.getTileRowIndex( playerPosition.y );
			auto playerDirection = m_aiBlackboard.getPlayerFacingDirection();
			auto oneTileAhead = tileMap.getTilePositionFrom( playerRow, playerCol, playerDirection );
			auto playerForward = oneTileAhead - playerPosition;
			return playerPosition + playerForward * 4.0f;
		}
		case EChaseStrategy::Whimsical:	// TODO
		case EChaseStrategy::Timid:		// TODO
		default:
			return Vector2f( 0.0f, 0.0f );
	}
}