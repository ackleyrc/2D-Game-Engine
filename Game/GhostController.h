#pragma once
#include <SparticleEngine.h>
#include "IMovementController.h"
#include "EntityMovement.h"

class SpriteComponent;
class AIBlackboard;
enum class EGhostPersonality;

class GhostController : public Component, public IMovementController
{
public:
	GhostController(
		EGhostPersonality personality,
		SpriteComponent& spriteComponent,
		AIBlackboard& aiBlackboard
	);

	~GhostController();

	void onAdd() override;
	void onUpdate( const float deltaTime ) override;

	EDirection updateDesiredDirection( float x, float y ) override;
	bool isWalkable( const ETileType tileType ) const override;

private:
	SpriteComponent& m_spriteComponent;
	AIBlackboard& m_aiBlackboard;

	EntityMovement m_entityMovement;
	EGhostPersonality m_personality;

	Vector2f getGoalPosition() const;
	Vector2f getScatterGoalPosition() const;
	Vector2f getChaseGoalPosition() const;
};