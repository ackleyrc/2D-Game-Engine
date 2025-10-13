#include <SparticleEngine.h>
#include <InputManager.h>
#include "Player.h"

void Player::onUpdate( float deltaTime )
{
	constexpr float playerSpeed = 100.0f;

	float horizontalAxis = input().getAxisHorizontal();
	float verticalAxis = input().getAxisVertical();

	x += ( horizontalAxis * playerSpeed * deltaTime );
	y += ( verticalAxis * playerSpeed * deltaTime );
}