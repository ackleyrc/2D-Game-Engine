#include "PelletManager.h"
#include "SparticleEngine.h"
#include "GameConfig.h"
#include "TileMap.h"
#include "ETileType.h"

PelletManager::PelletManager( SparticleEngine& engine, TileMap& tileMap ) :
	m_engine( engine ),
	m_tileMap( tileMap )
{ }

void PelletManager::generatePellets()
{
	for ( int rowIndex = 0; rowIndex < GameConfig::TILE_ROWS; ++rowIndex )
	{
		for ( int colIndex = 0; colIndex < GameConfig::TILE_COLS; ++colIndex )
		{
			ETileType tileType = m_tileMap.getTileType( rowIndex, colIndex );

			switch ( tileType )
			{
				case ETileType::Junction_Pellet:
				case ETileType::Path_Pellet:
				{
					auto pellet = m_engine.createGameObject();
					pellet->x = colIndex * GameConfig::TILE_WIDTH;
					pellet->y = rowIndex * GameConfig::TILE_HEIGHT;

					auto& spriteComponent = pellet->addComponent<SpriteComponent>();
					spriteComponent.setSprite( { "spritesheet", "pellet" } );
					
					break;
				}

				case ETileType::Junction_PowerPellet:
				case ETileType::Path_PowerPellet:
				{
					auto powerPellet = m_engine.createGameObject();
					powerPellet->x = colIndex * GameConfig::TILE_WIDTH;
					powerPellet->y = rowIndex * GameConfig::TILE_HEIGHT;

					auto& spriteComponent = powerPellet->addComponent<SpriteComponent>();
					spriteComponent.setSprite( { "spritesheet", "power_pellet" } );

					break;
				}

				default:
					continue;
			}
		}
	}
}