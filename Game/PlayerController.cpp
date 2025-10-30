#include <cmath>
#include <algorithm>
#include <SparticleEngine.h>
#include <InputManager.h>
#include "PlayerController.h"

void PlayerController::onUpdate( float deltaTime )
{
	constexpr float playerSpeed = 200.0f;

	float horizontalAxis = engine().input().getAxisHorizontal();
	float verticalAxis = engine().input().getAxisVertical();

	if ( abs(horizontalAxis) > 0.1f )
	{
		float x = m_gameObject->x;
		float fromX = x + ( horizontalAxis * playerSpeed * deltaTime );
		m_gameObject->x = std::clamp( fromX, 0.0f, 448.0f - 32.0f );
	}
	else if ( abs(verticalAxis) > 0.1f )
	{
		float y = m_gameObject->y;
		float fromY = y - ( verticalAxis * playerSpeed * deltaTime );
		m_gameObject->y = std::clamp( fromY, 0.0f, 512.0f - 32.0f * 3.0f );
	}
}