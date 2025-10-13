#pragma once
#include <GameObject.h>

class Player : public GameObject
{
public:
	using GameObject::GameObject;

	void onUpdate( float deltaTime ) override;

private:
	float m_movementSpeed = 100.0f;
};