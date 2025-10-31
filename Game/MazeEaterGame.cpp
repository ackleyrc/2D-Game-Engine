#include "MazeEaterGame.h"
#include "PlayerController.h"
#include "GameConfig.h"

void MazeEaterGame::onInit()
{
	m_engine->resources().loadSpriteSheet(
		"spritesheet",
		"assets/textures/spritesheet.png",
		"assets/textures/spritesheet.atlas"
	);

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
	m_player->y = GameConfig::TILE_HEIGHT * 4.0f;

	auto& spriteComponent = m_player->addComponent<SpriteComponent>();
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
}