#pragma once
#include "EngineAPI.h"

struct SPARTICLE_API Color
{
	Color( float r, float g, float b, float a ) 
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 0.0f;
};