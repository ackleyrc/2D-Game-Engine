#include <SparticleEngine.h>
#include "MazeEaterGame.h"
#include "PlayerController.h"

void MazeEaterGame::onInit()
{
	m_engine->resources().loadSpriteSheet(
		"spritesheet",
		"assets/textures/spritesheet.png",
		"assets/textures/spritesheet.atlas"
	);

	Sprite playerSprite = { "spritesheet", "ghost_dead_blue" };

	m_player = m_engine->createObject<GameObject>();
	m_player->addComponent<PlayerController>();
	m_player->setSprite( playerSprite );
}

void MazeEaterGame::onUpdate( float deltaTime )
{ }

void MazeEaterGame::onShutdown()
{ 
	m_engine->resources().unloadSpriteResource( "spritesheet" );
}