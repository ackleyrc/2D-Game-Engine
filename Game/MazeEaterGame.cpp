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

MazeEaterGame::MazeEaterGame() = default;
MazeEaterGame::~MazeEaterGame() = default;

void MazeEaterGame::onInit()
{
	m_scoreManager = std::make_unique<ScoreManager>( *m_engine );

	m_tileMap = std::make_unique<TileMap>( m_engine->resources() );
	m_tileMap->loadTileTypesFromFile( "assets/map-data/maze1.txt" );
	m_tileMap->loadTileRotationsFromFile( "assets/map-data/maze1_rotation.txt" );

	m_pelletManager = std::make_unique<PelletManager>( *m_engine, *m_tileMap );
	m_pelletManager->generatePellets();

	m_engine->resources().loadSpriteSheet(
		"spritesheet",
		"assets/textures/spritesheet.png",
		"assets/textures/spritesheet.atlas"
	);
	
	for ( int rowIndex = 0; rowIndex < GameConfig::TILE_ROWS; ++rowIndex )
	{
		for ( int colIndex = 0; colIndex < GameConfig::TILE_COLS; ++colIndex )
		{
			auto tileType = m_tileMap->getTileTypeForRowCol( rowIndex, colIndex );
			if ( (tileType >= ETileType::Wall_00 && tileType <= ETileType::Wall_09) ||
				  tileType == ETileType::GhostHomeGate )
			{
				auto wall = m_engine->createGameObject();
				wall->x = colIndex * GameConfig::TILE_WIDTH;
				wall->y = rowIndex * GameConfig::TILE_HEIGHT;

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

	auto playerUpAnimation = m_engine->resources().createAnimation(
		"player_up",
		{ playerUpClosedSprite, playerUpNarrowSprite, playerUpWideSprite, playerUpNarrowSprite },
		0.05f,
		true
	);

	auto playerDownAnimation = m_engine->resources().createAnimation(
		"player_down",
		{ playerDownClosedSprite, playerDownNarrowSprite, playerDownWideSprite, playerDownNarrowSprite },
		0.05f,
		true
	);
	
	auto playerLeftAnimation = m_engine->resources().createAnimation(
		"player_left",
		{ playerLeftClosedSprite, playerLeftNarrowSprite, playerLeftWideSprite, playerLeftNarrowSprite },
		0.05f,
		true
	);

	auto playerRightAnimation = m_engine->resources().createAnimation(
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

	m_player = m_engine->createGameObject();
	m_player->x = GameConfig::SCREEN_WIDTH * 0.5f - GameConfig::TILE_WIDTH * 0.5f;
	m_player->y = GameConfig::SCREEN_HEIGHT - GameConfig::TILE_HEIGHT * 10.0f;

	auto& playerSpriteComponent = m_player->addComponent<SpriteComponent>( 1 );
	playerSpriteComponent.setSprite( playerLeftClosedSprite );
	playerSpriteComponent.setPositionOffset( -GameConfig::TILE_WIDTH * 0.5f, -GameConfig::TILE_HEIGHT * 0.5f );

	auto& directionSpriteComponent = m_player->addComponent<SpriteComponent>( 1 );
	directionSpriteComponent.setSprite( playerMoveDirectionSprite );
	directionSpriteComponent.setEnabled( false );
	directionSpriteComponent.setRotationPivot(
		GameConfig::TILE_WIDTH,
		GameConfig::TILE_HEIGHT
	);

	auto& animationComponent = m_player->addComponent<AnimationComponent>( playerSpriteComponent );
	animationComponent.setAnimation( playerLeftAnimation );

	auto& playerController = m_player->addComponent<PlayerController>(
		directionSpriteComponent,
		animationComponent,
		playerUpAnimation,
		playerDownAnimation,
		playerLeftAnimation,
		playerRightAnimation,
		*m_tileMap
	);

	auto ghostAStartPositon = Vector2f(
		GameConfig::SCREEN_WIDTH * 0.5f - GameConfig::TILE_WIDTH * 0.5f,
		GameConfig::SCREEN_HEIGHT - GameConfig::TILE_HEIGHT * 4.0f
	);

	m_ghostA = spawnGhost( EChaseStrategy::Aggressive, ghostAStartPositon, ghostWhiteSprite, playerController );

	auto ghostBStartPosition = Vector2f(
		GameConfig::SCREEN_WIDTH * 0.5f - GameConfig::TILE_WIDTH * 0.5f,
		GameConfig::SCREEN_HEIGHT - GameConfig::TILE_HEIGHT * 16.0f
	);

	m_ghostB = spawnGhost( EChaseStrategy::Cunning, ghostBStartPosition, ghostWhiteSprite, playerController );
}

GameObject* MazeEaterGame::spawnGhost(
	EChaseStrategy chaseStrategy,
	Vector2f startPosition,
	Sprite ghostSprite,
	PlayerController& playerController
)
{
	auto ghost = m_engine->createGameObject();
	ghost->x = startPosition.x;
	ghost->y = startPosition.y;

	auto& ghostSpriteComponent = ghost->addComponent<SpriteComponent>( 1 );
	ghostSpriteComponent.setSprite( ghostSprite );
	ghostSpriteComponent.setPositionOffset( -GameConfig::TILE_WIDTH * 0.5f, -GameConfig::TILE_HEIGHT * 0.5f );

	ghost->addComponent<GhostController>(
		chaseStrategy,
		ghostSpriteComponent,
		*m_tileMap,
		playerController
	);

	return ghost;
}

void MazeEaterGame::onUpdate( float deltaTime )
{
	m_pelletManager->onUpdate( m_player );
}

void MazeEaterGame::onShutdown()
{ 
	m_engine->resources().unloadSpriteResource( "spritesheet" );
	m_engine->resources().unloadTextFile( "assets/map-data/maze1.txt" );
}