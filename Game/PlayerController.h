#pragma once
#include <Component.h>
#include "TileMap.h"

class AnimationComponent;
struct AnimationData;
enum class ETileType;

class PlayerController : public Component
{
public:
	PlayerController(
		AnimationComponent& animationComponent,
		const AnimationData* playerUp,
		const AnimationData* playerDown,
		const AnimationData* playerLeft,
		const AnimationData* playerRight,
		TileMap& tileMap
	);

	~PlayerController() { }

	void onUpdate( float deltaTime ) override;

private:
	AnimationComponent& m_animationComponent;
	const AnimationData* m_playerUp;
	const AnimationData* m_playerDown;
	const AnimationData* m_playerLeft;
	const AnimationData* m_playerRight;

	enum class EDirection { NONE, UP, LEFT, DOWN, RIGHT };
	EDirection m_currentDirection = EDirection::NONE;

	const EDirection getInputDirection() const;

	TileMap& m_tileMap;

	static bool isWalkable( const ETileType tileType );

	static bool canAdvanceToNextTile(
		const float x,
		const float y,
		EDirection currentDirection,
		const TileMap& tileMap
	);

	static bool canStartMovingInDirection(
		const float x,
		const float y,
		EDirection newDirection,
		const TileMap& tileMap
	);
};