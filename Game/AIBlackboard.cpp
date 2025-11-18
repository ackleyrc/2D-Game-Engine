#include "AIBlackboard.h"
#include <SparticleEngine.h>
#include "TileMap.h"
#include "EDirection.h"

AIBlackboard::AIBlackboard( 
	TileMap& tileMap 
) : m_tileMap( tileMap )
{
	m_playerPosition = Vector2f();
	m_playerDirection = EDirection::NONE;
	m_ghostPositions = {};
}

AIBlackboard::~AIBlackboard() = default;

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