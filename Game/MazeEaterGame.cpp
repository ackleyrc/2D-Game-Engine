#include "MazeEaterGame.h"
#include "PlayerController.h"

void MazeEaterGame::onInit()
{
	m_engine->resources().loadSpriteSheet(
		"spritesheet",
		"assets/textures/spritesheet.png",
		"assets/textures/spritesheet.atlas"
	);

	Sprite ghostBlueSprite = { "spritesheet", "ghost_dead_blue" };
	Sprite ghostWhiteSprite = { "spritesheet", "ghost_dead_white" };

	auto ghostDeadAnimation = m_engine->resources().createAnimation(
		"ghost_dead",
		{ ghostBlueSprite, ghostWhiteSprite },
		0.5f,
		true
	);

	m_player = m_engine->createObject<GameObject>();
	m_player->addComponent<PlayerController>();

	auto& spriteComponent = m_player->addComponent<SpriteComponent>();
	spriteComponent.setSprite( ghostBlueSprite );

	auto& animationComponent = m_player->addComponent<AnimationComponent>( spriteComponent );
	animationComponent.setAnimation( ghostDeadAnimation );
	animationComponent.play();
}

void MazeEaterGame::onUpdate( float deltaTime )
{ }

void MazeEaterGame::onShutdown()
{ 
	m_engine->resources().unloadSpriteResource( "spritesheet" );
}