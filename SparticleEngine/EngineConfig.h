#pragma once
#include <string>

struct EngineConfig
{
	int width = 448;
	int height = 512;
	std::string windowTitle = "Untitled Game";
	bool resizable = true;
};