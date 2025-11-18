#pragma once
#include <SparticleEngine.h>
#include "IMovementController.h"
#include "EntityMovement.h"

class SpriteComponent;
class TileMap;
class PlayerController;
enum class EChaseStrategy;

class GhostController : public Component, public IMovementController
{
public:
	GhostController(
		EChaseStrategy chaseStrategy,
		SpriteComponent& spriteComponent,
		TileMap& tileMap,
		PlayerController& playerController
	);

	~GhostController();

	void onAdd() override;
	void onUpdate( const float deltaTime ) override;

	EDirection updateDesiredDirection( float x, float y ) override;
	bool isWalkable( const ETileType tileType ) const override;

private:
	SpriteComponent& m_spriteComponent;
	TileMap& m_tileMap;
	PlayerController& m_playerController;

	EntityMovement m_entityMovement;
	EChaseStrategy m_chaseStrategy;

	Vector2f getGoalPosition() const;
};