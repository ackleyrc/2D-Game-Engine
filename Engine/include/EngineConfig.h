#pragma once
#include <string>
#include "EngineAPI.h"
#include "Color.h"

struct SPARTICLE_API EngineConfig
{
	int width = 800;
	int height = 600;
	std::string windowTitle = "Untitled Game";
	Color backgroundColor = Color( 0.0f, 0.0f, 0.0f, 1.0f );
	bool resizable = true;
};