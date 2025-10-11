#pragma once
#include <SDL3/SDL.h>

struct SDLState
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int width = 1600;
	int height = 900;
};