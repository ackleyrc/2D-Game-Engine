#include "MazeEaterGame.h"
#include "SparticleEngine.h"
#include "PlayerController.h"
#include "GhostController.h"
#include "GameConfig.h"
#include "TileMap.h"
#include "ETileType.h"
#include "PelletManager.h"
#include "ScoreManager.h"
#include "EChaseStrategy.h"
#include "AIBlackboard.h"

MazeEaterGame::MazeEaterGame() = default;
MazeEaterGame::~MazeEaterGame() = default;

void MazeEaterGame::onInit()
{
	initResources();
	initScore();
	initTileMap();
	initPellets();
	spawnLevelGeometry();
	createAnimations();
	spawnPlayer();
	initAiBlackboard();
	spawnGhosts();
}

void MazeEaterGame::initScore()
{
	m_scoreManager = std::make_unique<ScoreManager>( *m_engine );
}

void MazeEaterGame::initTileMap()
{
	m_tileMap = std::make_unique<TileMap>( m_engine->resources() );
	m_tileMap->loadTileTypesFromFile( "assets/map-data/maze1.txt" );
	m_tileMap->loadTileRotationsFromFile( "assets/map-data/maze1_rotation.txt" );
}

void MazeEaterGame::initPellets()
{
	m_pelletManager = std::make_unique<PelletManager>( *m_engine, *m_tileMap );
	m_pelletManager->generatePellets();
}

void MazeEaterGame::initResources()
{
	m_engine->resources().loadSpriteSheet(
		"spritesheet",
		"assets/textures/spritesheet.png",
		"assets/textures/spritesheet.atlas"
	);
}

void MazeEaterGame::spawnLevelGeometry()
{
	for ( int rowIndex = 0; rowIndex < GameConfig::TILE_ROWS; ++rowIndex )
	{
		for ( int colIndex = 0; colIndex < GameConfig::TILE_COLS; ++colIndex )
		{
			auto tileType = m_tileMap->getTileTypeForRowCol( rowIndex, colIndex );
			if ( ( tileType >= ETileType::Wall_00 && tileType <= ETileType::Wall_09 ) ||
				tileType == ETileType::GhostHomeGate )
			{
				auto wall = m_engine->createGameObject();
				wall->position.x = colIndex * GameConfig::TILE_WIDTH;
				wall->position.y = rowIndex * GameConfig::TILE_HEIGHT;

				auto& spriteComponent = wall->addComponent<SpriteComponent>();
				spriteComponent.setSprite( m_tileMap->getSprite( tileType ) );

				auto degrees = m_tileMap->getTileRotationDegrees( rowIndex, colIndex );
				spriteComponent.setRotationDegrees( degrees );
				spriteComponent.setRotationPivot(
					GameConfig::TILE_WIDTH * 0.5f,
					GameConfig::TILE_HEIGHT * 0.5f
				);
			}
		}
	}
}

void MazeEaterGame::createAnimations()
{
	Sprite playerUpNarrowSprite = { "spritesheet", "player_up_1" };
	Sprite playerUpWideSprite = { "spritesheet", "player_up_2" };
	Sprite playerUpClosedSprite = { "spritesheet", "player_up_3" };

	Sprite playerDownNarrowSprite = { "spritesheet", "player_down_1" };
	Sprite playerDownWideSprite = { "spritesheet", "player_down_2" };
	Sprite playerDownClosedSprite = { "spritesheet", "player_down_3" };

	Sprite playerLeftNarrowSprite = { "spritesheet", "player_left_1" };
	Sprite playerLeftWideSprite = { "spritesheet", "player_left_2" };
	Sprite playerLeftClosedSprite = { "spritesheet", "player_left_3" };

	Sprite playerRightNarrowSprite = { "spritesheet", "player_right_1" };
	Sprite playerRightWideSprite = { "spritesheet", "player_right_2" };
	Sprite playerRightClosedSprite = { "spritesheet", "player_right_3" };

	Sprite playerMoveDirectionSprite = { "spritesheet", "move_direction" };

	Sprite ghostBlueSprite = { "spritesheet", "ghost_dead_blue" };
	Sprite ghostWhiteSprite = { "spritesheet", "ghost_dead_white" };

	m_defaultPlayerSprite = playerLeftClosedSprite;
	m_playerMoveDirectionSprite = playerMoveDirectionSprite;

	m_tempGhostSprite = ghostWhiteSprite;

	m_playerUpAnimation = m_engine->resources().createAnimation(
		"player_up",
		{ playerUpClosedSprite, playerUpNarrowSprite, playerUpWideSprite, playerUpNarrowSprite },
		0.05f,
		true
	);

	m_playerDownAnimation = m_engine->resources().createAnimation(
		"player_down",
		{ playerDownClosedSprite, playerDownNarrowSprite, playerDownWideSprite, playerDownNarrowSprite },
		0.05f,
		true
	);

	m_playerLeftAnimation = m_engine->resources().createAnimation(
		"player_left",
		{ playerLeftClosedSprite, playerLeftNarrowSprite, playerLeftWideSprite, playerLeftNarrowSprite },
		0.05f,
		true
	);

	m_playerRightAnimation = m_engine->resources().createAnimation(
		"player_right",
		{ playerRightClosedSprite, playerRightNarrowSprite, playerRightWideSprite, playerRightNarrowSprite },
		0.05f,
		true
	);

	auto ghostDeadAnimation = m_engine->resources().createAnimation(
		"ghost_dead",
		{ ghostBlueSprite, ghostWhiteSprite },
		0.5f,
		true
	);
}

void MazeEaterGame::spawnPlayer()
{
	m_player = m_engine->createGameObject();
	m_player->position.x = GameConfig::SCREEN_WIDTH * 0.5f - GameConfig::TILE_WIDTH * 0.5f;
	m_player->position.y = GameConfig::SCREEN_HEIGHT - GameConfig::TILE_HEIGHT * 10.0f;

	auto& playerSpriteComponent = m_player->addComponent<SpriteComponent>( 1 );
	playerSpriteComponent.setSprite( m_defaultPlayerSprite );
	playerSpriteComponent.setPositionOffset( -GameConfig::TILE_WIDTH * 0.5f, -GameConfig::TILE_HEIGHT * 0.5f );

	auto& directionSpriteComponent = m_player->addComponent<SpriteComponent>( 1 );
	directionSpriteComponent.setSprite( m_playerMoveDirectionSprite );
	directionSpriteComponent.setEnabled( false );
	directionSpriteComponent.setRotationPivot(
		GameConfig::TILE_WIDTH,
		GameConfig::TILE_HEIGHT
	);

	auto& animationComponent = m_player->addComponent<AnimationComponent>( playerSpriteComponent );
	animationComponent.setAnimation( m_playerLeftAnimation );

	auto& playerController = m_player->addComponent<PlayerController>(
		directionSpriteComponent,
		animationComponent,
		m_playerUpAnimation,
		m_playerDownAnimation,
		m_playerLeftAnimation,
		m_playerRightAnimation,
		*m_tileMap
	);

	m_playerController = &playerController;
}

void MazeEaterGame::initAiBlackboard()
{
	m_aiBlackboard = std::make_unique<AIBlackboard>( *m_tileMap );
}

void MazeEaterGame::spawnGhosts()
{
	auto startPositionA = Vector2f(
		GameConfig::SCREEN_WIDTH * 0.5f - GameConfig::TILE_WIDTH * 0.5f,
		GameConfig::SCREEN_HEIGHT - GameConfig::TILE_HEIGHT * 4.0f
	);

	m_ghostA = spawnGhost( EChaseStrategy::Aggressive, startPositionA );

	auto startPositionB = Vector2f(
		GameConfig::SCREEN_WIDTH * 0.5f - GameConfig::TILE_WIDTH * 0.5f,
		GameConfig::SCREEN_HEIGHT - GameConfig::TILE_HEIGHT * 16.0f
	);

	m_ghostB = spawnGhost( EChaseStrategy::Cunning, startPositionB );
}

GameObject* MazeEaterGame::spawnGhost( 
	EChaseStrategy chaseStrategy, 
	const Vector2f startPosition 
)
{
	auto ghost = m_engine->createGameObject();
	ghost->position = startPosition;

	auto& ghostSpriteComponent = ghost->addComponent<SpriteComponent>( 1 );
	ghostSpriteComponent.setSprite( m_tempGhostSprite );
	ghostSpriteComponent.setPositionOffset( -GameConfig::TILE_WIDTH * 0.5f, -GameConfig::TILE_HEIGHT * 0.5f );

	ghost->addComponent<GhostController>(
		chaseStrategy,
		ghostSpriteComponent,
		*m_aiBlackboard
	);

	return ghost;
}

void MazeEaterGame::onUpdate( float deltaTime )
{
	m_pelletManager->onUpdate( m_player );

	m_aiBlackboard->setPlayerPosition( m_player->position );
	m_aiBlackboard->setPlayerFacingDirection( m_playerController->getCurrentDirection() );

	m_aiBlackboard->setGhostPosition( GHOST_A_ID, m_ghostA->position );
	m_aiBlackboard->setGhostPosition( GHOST_B_ID, m_ghostB->position );
}

void MazeEaterGame::onShutdown()
{ 
	m_engine->resources().unloadSpriteResource( "spritesheet" );
	m_engine->resources().unloadTextFile( "assets/map-data/maze1.txt" );
}