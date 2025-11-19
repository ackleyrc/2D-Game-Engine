#include "AIBlackboard.h"
#include <stdexcept>
#include <SparticleEngine.h>
#include "TileMap.h"
#include "EDirection.h"
#include "EGhostMode.h"

AIBlackboard::AIBlackboard( 
	TileMap& tileMap 
) : m_tileMap( tileMap )
{
	m_playerPosition = Vector2f();
	m_playerDirection = EDirection::NONE;
	m_ghostPositions = {};
	m_currentGhostMode = EGhostMode::Scatter;
	m_scatterTimeElapsed = 0.0f;
	m_chaseTimeElapsed = 0.0f;
}

AIBlackboard::~AIBlackboard() = default;

void AIBlackboard::updateGhostMode( const float deltaTime )
{
	switch ( m_currentGhostMode )
	{
		case EGhostMode::Scatter:

			m_scatterTimeElapsed += deltaTime;

			// TODO: Dynamic duration based on level and scatter wave
			if ( m_scatterTimeElapsed >= 7.0f ) {
				m_scatterTimeElapsed -= 7.0f;
				m_currentGhostMode = EGhostMode::Chase;
			}

			break;

		case EGhostMode::Chase:

			m_chaseTimeElapsed += deltaTime;

			// TODO: Dynamic duration based on level and chase wave
			if ( m_chaseTimeElapsed >= 20.0f ) {
				m_chaseTimeElapsed -= 20.0f;
				m_currentGhostMode = EGhostMode::Scatter;
			}

			break;

		default:

			throw std::invalid_argument( "Unrecognized Ghost Mode" );
	}
}

EGhostMode AIBlackboard::getGhostMode() const
{
	return m_currentGhostMode;
}

TileMap& AIBlackboard::getTileMap() const
{
	return m_tileMap;
}

void AIBlackboard::setPlayerPosition( const Vector2f& position )
{
	m_playerPosition = position;
}

Vector2f AIBlackboard::getPlayerPosition() const
{
	return m_playerPosition;
}

void AIBlackboard::setGhostPosition( int ghostId, const Vector2f& position )
{
	m_ghostPositions[ghostId] = position;
}

Vector2f AIBlackboard::getGhostPosition( int ghostId ) const
{
	Vector2f position = m_ghostPositions.at(ghostId);
	return position;
}

void AIBlackboard::setPlayerFacingDirection( EDirection direction )
{
	m_playerDirection = direction;
}

EDirection AIBlackboard::getPlayerFacingDirection() const
{
	return m_playerDirection;
}