#pragma once

class SparticleEngine;

class IGame {
public:
	virtual ~IGame() = default;
	virtual void onInit() = 0;
	virtual void onUpdate( float deltaTime ) = 0;
	virtual void onShutdown() = 0;
	virtual void setEngine( SparticleEngine* engine ) = 0;
};