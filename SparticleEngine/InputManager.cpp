#include "InputManager.h"

void InputManager::update()
{
	const bool* state = SDL_GetKeyboardState( nullptr );

	m_axisHorizontal = ( state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT] ? 1.0f : 0.0f )
					 - ( state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT] ? 1.0f : 0.0f );

	m_axisVertical = ( state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP] ? 1.0f : 0.0f )
				   - ( state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN] ? 1.0f : 0.0f );
}