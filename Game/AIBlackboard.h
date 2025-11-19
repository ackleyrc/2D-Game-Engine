#pragma once
#include <unordered_map>
#include <SparticleEngine.h>

class TileMap;
enum class EDirection;
enum class EGhostMode;

class AIBlackboard 
{
public:
	AIBlackboard( TileMap& tileMap );
	~AIBlackboard();

	void updateGhostMode( const float deltaTime );
	EGhostMode getGhostMode() const;

	TileMap& getTileMap() const;

	void setPlayerPosition( const Vector2f& position );
	Vector2f getPlayerPosition() const;

	void setGhostPosition( int ghostId, const Vector2f& position );
	Vector2f getGhostPosition( int ghostId ) const;

	void setPlayerFacingDirection( EDirection direction );
	EDirection getPlayerFacingDirection() const;

private:
	TileMap& m_tileMap;

	Vector2f m_playerPosition;
	EDirection m_playerDirection;

	std::unordered_map<int, Vector2f> m_ghostPositions;

	EGhostMode m_currentGhostMode;
	float m_scatterTimeElapsed;
	float m_chaseTimeElapsed;
};