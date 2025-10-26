#pragma once
#include <Component.h>

class PlayerController : public Component
{
public:
	PlayerController() { }

	void onUpdate( float deltaTime ) override;
};