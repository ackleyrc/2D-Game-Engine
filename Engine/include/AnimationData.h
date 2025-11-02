#pragma once
#include <vector>
#include "EngineAPI.h"

struct Sprite;

struct SPARTICLE_API AnimationData
{
	std::vector<Sprite> frames;
	float frameDuration;
	bool loop;
};