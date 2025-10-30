#pragma once
#include <Component.h>

class PlayerController : public Component
{
public:
	PlayerController() { }
	~PlayerController() { }

	void onUpdate( float deltaTime ) override;
};