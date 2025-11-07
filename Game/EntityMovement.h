#pragma once
#include <functional>

class GameObject;
class IMovementController;
enum class EDirection;
enum class ETileType;
class TileMap;

class EntityMovement {
public:
	EntityMovement( IMovementController& controller, TileMap& tileMap );
	~EntityMovement();

	void update( GameObject* gameObject, const float deltaTime );
	void setSpeed( float speed ) { m_speed = speed; }

	EDirection getCurrentDirection() const { return m_currentDirection; }

	bool canStartMovingInDirection(
		float x,
		float y,
		EDirection newDirection,
		const TileMap& tileMap
	);

	bool canAdvanceToNextTile(
		float x,
		float y,
		EDirection currentDirection,
		const TileMap& tileMap
	);

private:
	IMovementController& m_controller;
	EDirection m_currentDirection;
	TileMap& m_tileMap;
	float m_speed = 100.0f;
};