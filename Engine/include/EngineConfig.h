#pragma once
#include <string>
#include "EngineAPI.h"

struct SPARTICLE_API EngineConfig
{
	int width = 800;
	int height = 600;
	std::string windowTitle = "Untitled Game";
	bool resizable = true;
};