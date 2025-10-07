#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>

class InputManager
{
public:
	void update();

	float getAxisHorizontal() const { return m_axisHorizontal; }
	float getAxisVertical() const { return m_axisVertical; }

private:
	float m_axisHorizontal = 0.0f;
	float m_axisVertical = 0.0f;
};