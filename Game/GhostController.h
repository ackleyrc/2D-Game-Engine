#pragma once
#include <Component.h>
#include "IMovementController.h"
#include "EntityMovement.h"

class SpriteComponent;
class TileMap;

class GhostController : public Component, public IMovementController
{
public:
	GhostController(
		SpriteComponent& spriteComponent,
		TileMap& tileMap
	);

	~GhostController();

	void onAdd() override;
	void onUpdate( const float deltaTime ) override;

	EDirection updateDesiredDirection( float x, float y ) override;
	bool isWalkable( const ETileType tileType ) const override;

private:
	SpriteComponent& m_spriteComponent;
	TileMap& m_tileMap;

	EntityMovement m_entityMovement;
};