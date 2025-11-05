#pragma once
#include <vector>

class SparticleEngine;
class GameObject;
class TileMap;
enum class ETileType;

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
	static EPelletType getPelletType( const ETileType tileType );

	std::vector<std::vector<GameObject*>> m_allPellets;
	std::vector<GameObject*> m_powerPellets;

	void updatePelletConsumption( GameObject* player );
	void updatePowerPelletBlinking();
};