#include "MazeEaterGame.h"
#include "PlayerController.h"
#include "GameConfig.h"
#include "TileMap.h"
#include "ETileType.h"

void MazeEaterGame::onInit()
{
	TileMap tileMap( m_engine->resources() );
	tileMap.loadTileTypesFromFile( "assets/map-data/maze1.txt" );
	tileMap.loadTileRotationsFromFile( "assets/map-data/maze1_rotation.txt" );

	m_engine->resources().loadSpriteSheet(
		"spritesheet",
		"assets/textures/spritesheet.png",
		"assets/textures/spritesheet.atlas"
	);
	
	// TODO: Set specific sprite according to tile type & rotate appropriately
	Sprite tempWallSprite = { "spritesheet", "level_a_thin_inner_corner" };

	for ( int rowIndex = 0; rowIndex < GameConfig::TILE_ROWS; ++rowIndex )
	{
		for ( int colIndex = 0; colIndex < GameConfig::TILE_COLS; ++colIndex )
		{
			auto tileType = tileMap.getTileType( rowIndex, colIndex );
			if ( (tileType >= ETileType::Wall_00 && tileType <= ETileType::Wall_09) ||
				  tileType == ETileType::GhostHomeGate )
			{
				auto wall = m_engine->createGameObject();
				wall->x = colIndex * GameConfig::TILE_WIDTH;
				wall->y = rowIndex * GameConfig::TILE_HEIGHT;

				auto& spriteComponent = wall->addComponent<SpriteComponent>();
				spriteComponent.setSprite( tileMap.getSprite( tileType ) );

				auto degrees = tileMap.getTileRotationDegrees( rowIndex, colIndex );
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
	m_player->x = GameConfig::SCREEN_WIDTH * 0.5f - GameConfig::TILE_WIDTH;
	m_player->y = GameConfig::SCREEN_HEIGHT - GameConfig::TILE_HEIGHT * 10.5f;

	auto& spriteComponent = m_player->addComponent<SpriteComponent>(1);
	spriteComponent.setSprite( ghostBlueSprite );

	auto& animationComponent = m_player->addComponent<AnimationComponent>( spriteComponent );
	animationComponent.setAnimation( playerLeftAnimation );

	m_player->addComponent<PlayerController>(
		animationComponent,
		playerUpAnimation,
		playerDownAnimation,
		playerLeftAnimation,
		playerRightAnimation
	);
}

void MazeEaterGame::onUpdate( float deltaTime )
{ }

void MazeEaterGame::onShutdown()
{ 
	m_engine->resources().unloadSpriteResource( "spritesheet" );
	m_engine->resources().unloadTextFile( "assets/map-data/maze1.txt" );
}