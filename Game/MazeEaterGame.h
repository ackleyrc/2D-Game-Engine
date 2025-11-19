#pragma once
#include <memory>
#include "IGame.h"
#include "Sprite.h"

class SparticleEngine;
class GameObject;
class TileMap;
class PelletManager;
class ScoreManager;
class PlayerController;
class AIBlackboard;
struct AnimationData;
class Vector2f;
enum class EGhostPersonality;

class MazeEaterGame : public IGame
{
public:
	MazeEaterGame();
	~MazeEaterGame() override;

	void setEngine( SparticleEngine* engine ) override { m_engine = engine; }

	void onInit() override;
	void onUpdate( float deltaTime ) override;
	void onShutdown() override;

	static constexpr int GHOST_A_ID = 0;
	static constexpr int GHOST_B_ID = 1;
	static constexpr int GHOST_C_ID = 2;
	static constexpr int GHOST_D_ID = 3;

private:
	SparticleEngine* m_engine = nullptr;

	GameObject* m_player = nullptr;
	GameObject* m_ghostA = nullptr;
	GameObject* m_ghostB = nullptr;

	std::unique_ptr<TileMap> m_tileMap;
	std::unique_ptr<PelletManager> m_pelletManager;
	std::unique_ptr<ScoreManager> m_scoreManager;
	std::unique_ptr<AIBlackboard> m_aiBlackboard;

	Sprite m_defaultPlayerSprite;
	Sprite m_playerMoveDirectionSprite;

	const AnimationData* m_playerUpAnimation = nullptr;
	const AnimationData* m_playerDownAnimation = nullptr;
	const AnimationData* m_playerLeftAnimation = nullptr;
	const AnimationData* m_playerRightAnimation = nullptr;

	Sprite m_tempGhostASprite;
	Sprite m_tempGhostBSprite;
	Sprite m_tempGhostCSprite;
	Sprite m_tempGhostDSprite;

	PlayerController* m_playerController = nullptr;

	void initResources();
	void initScore();
	void initTileMap();
	void initPellets();
	void spawnLevelGeometry();
	void createAnimations();
	void spawnPlayer();
	void initAiBlackboard();
	void spawnGhosts();

	GameObject* spawnGhost( 
		EGhostPersonality personality,
		const Vector2f& startPosition,
		const Sprite& initialSprite
	);
};