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
enum class EChaseStrategy;

class MazeEaterGame : public IGame
{
public:
	MazeEaterGame();
	~MazeEaterGame() override;

	void setEngine( SparticleEngine* engine ) override { m_engine = engine; }

	void onInit() override;
	void onUpdate( float deltaTime ) override;
	void onShutdown() override;

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

	const AnimationData* m_playerUpAnimation;
	const AnimationData* m_playerDownAnimation;
	const AnimationData* m_playerLeftAnimation;
	const AnimationData* m_playerRightAnimation;

	Sprite m_tempGhostSprite;

	PlayerController* m_playerController;

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
		EChaseStrategy chaseStrategy, 
		const Vector2f startPosition 
	);
};