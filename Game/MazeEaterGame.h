#pragma once
#include <memory>
#include "IGame.h"

class SparticleEngine;
class GameObject;
class TileMap;
class PelletManager;

class MazeEaterGame : public IGame
{
public:
	MazeEaterGame();
	~MazeEaterGame() override = default;

	void setEngine( SparticleEngine* engine ) override { m_engine = engine; }

	void onInit() override;
	void onUpdate( float deltaTime ) override;
	void onShutdown() override;

private:
	SparticleEngine* m_engine = nullptr;
	GameObject* m_player = nullptr;

	std::unique_ptr<TileMap> m_tileMap;
};