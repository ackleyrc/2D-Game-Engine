#pragma once
#include <vector>

class SparticleEngine;
class GameObject;
class TileMap;

class PelletManager {
public:
	PelletManager( SparticleEngine& engine, TileMap& tileMap );
	~PelletManager() = default;

	void generatePellets();
	void onUpdate( GameObject* player );

private:
	SparticleEngine& m_engine;
	TileMap& m_tileMap;

	enum class EPelletType { NONE, Pellet, PowerPellet };
	std::vector<std::vector<GameObject*>> m_pellets;
};