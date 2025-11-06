#pragma once
#include "EngineAPI.h"

class SparticleEngine;

class SPARTICLE_API IGame {
public:
	virtual ~IGame() = default;
	virtual void onInit() = 0;
	virtual void onUpdate( const float deltaTime ) = 0;
	virtual void onShutdown() = 0;
	virtual void setEngine( SparticleEngine* engine ) = 0;
};