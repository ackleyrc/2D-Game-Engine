#include "GhostController.h"
#include <SparticleEngine.h>
#include "TileMap.h"
#include "ETileType.h"
#include "EDirection.h"
#include "IMovementController.h"

GhostController::GhostController(
	SpriteComponent& spriteComponent,
	TileMap& tileMap
) : m_spriteComponent( spriteComponent ),
	m_tileMap( tileMap ),
	m_entityMovement( *this, tileMap )
{ }

GhostController::~GhostController() = default;

void GhostController::onAdd()
{
	m_entityMovement.setSpeed( 100.0f );
}

void GhostController::onUpdate( const float deltaTime )
{
	m_entityMovement.update( m_gameObject, deltaTime );
}

EDirection GhostController::updateDesiredDirection( float x, float y )
{
	auto currentDirection = m_entityMovement.getCurrentDirection();
	auto backtrackDirection = DirectionUtils::getOpposite( currentDirection );

	auto frame = m_gameObject->engine().getFramesElapsed();

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

		return direction;
	}

	return backtrackDirection;
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