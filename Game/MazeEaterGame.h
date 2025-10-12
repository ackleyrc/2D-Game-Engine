#pragma once
#include "IGame.h"

class MazeEaterGame : public IGame
{
public:
	void setEngine( SparticleEngine* engine ) override { m_engine = engine; }

	void onInit() override;
	void onUpdate( float deltaTime ) override;
	void onShutdown() override;

private:
	SparticleEngine* m_engine;

	GameObject* m_player = nullptr;
};