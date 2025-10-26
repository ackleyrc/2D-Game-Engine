#include <SparticleEngine.h>
#include <InputManager.h>
#include "PlayerController.h"

void PlayerController::onUpdate( float deltaTime )
{
	constexpr float playerSpeed = 100.0f;

	float horizontalAxis = engine().input().getAxisHorizontal();
	float verticalAxis = engine().input().getAxisVertical();

	m_gameObject->x += ( horizontalAxis * playerSpeed * deltaTime );
	m_gameObject->y += ( verticalAxis * playerSpeed * deltaTime );
}