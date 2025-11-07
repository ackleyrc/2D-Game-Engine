#pragma once
#include <Component.h>
#include "IMovementController.h"
#include "EntityMovement.h"

class TileMap;
class AnimationComponent;
struct AnimationData;
enum class ETileType;
enum class EDirection;

class PlayerController : public Component, public IMovementController
{
public:
	PlayerController(
		SpriteComponent& directionSpriteComponent,
		AnimationComponent& animationComponent,
		const AnimationData* playerUp,
		const AnimationData* playerDown,
		const AnimationData* playerLeft,
		const AnimationData* playerRight,
		TileMap& tileMap
	);

	~PlayerController() { }

	void onUpdate( const float deltaTime ) override;

	EDirection updateDesiredDirection() override;
	bool isWalkable( const ETileType tileType ) const override;

private:
	SpriteComponent& m_directionSpriteComponent;
	AnimationComponent& m_animationComponent;
	const AnimationData* m_playerUp;
	const AnimationData* m_playerDown;
	const AnimationData* m_playerLeft;
	const AnimationData* m_playerRight;
	EntityMovement m_entityMovement;

	EDirection m_lastInputDirection;

	const EDirection getInputDirection() const;

	TileMap& m_tileMap;

	void updateAnimation( EDirection movementDirection );
	void updateDirectionSprite();
};