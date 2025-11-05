#include "PelletManager.h"
#include "SparticleEngine.h"
#include "GameConfig.h"
#include "TileMap.h"
#include "ETileType.h"
#include "GameEvents.h"

PelletManager::PelletManager( SparticleEngine& engine, TileMap& tileMap ) :
	m_engine( engine ),
	m_tileMap( tileMap )
{ }

void PelletManager::generatePellets()
{
	for ( int rowIndex = 0; rowIndex < GameConfig::TILE_ROWS; ++rowIndex )
	{
		std::vector<GameObject*> row;

		for ( int colIndex = 0; colIndex < GameConfig::TILE_COLS; ++colIndex )
		{
			ETileType tileType = m_tileMap.getTileType( rowIndex, colIndex );

			switch ( getPelletType( tileType ) )
			{
				case EPelletType::Pellet:
				{
					auto pellet = m_engine.createGameObject();
					pellet->x = colIndex * GameConfig::TILE_WIDTH;
					pellet->y = rowIndex * GameConfig::TILE_HEIGHT;

					auto& spriteComponent = pellet->addComponent<SpriteComponent>();
					spriteComponent.setSprite( { "spritesheet", "pellet" } );

					row.push_back( pellet );
					break;
				}

				case EPelletType::PowerPellet:
				{
					auto powerPellet = m_engine.createGameObject();
					powerPellet->x = colIndex * GameConfig::TILE_WIDTH;
					powerPellet->y = rowIndex * GameConfig::TILE_HEIGHT;

					m_powerPellets.push_back( powerPellet );

					auto& spriteComponent = powerPellet->addComponent<SpriteComponent>();
					spriteComponent.setSprite( { "spritesheet", "power_pellet" } );

					row.push_back( powerPellet );
					break;
				}

				default:

					row.push_back( nullptr );
					break;
			}
		}

		m_allPellets.push_back( std::move( row ) );
	}
}

void PelletManager::onUpdate( GameObject* player )
{
	updatePelletConsumption( player );

	updatePowerPelletBlinking();
}

void PelletManager::updatePelletConsumption( GameObject* player )
{
	float playerX = player->x;
	float playerY = player->y;

	int playerRowIndex = static_cast<int>( playerY / GameConfig::TILE_HEIGHT );
	int playerColIndex = static_cast<int>( playerX / GameConfig::TILE_WIDTH );

	// Only cardinal neighbor pellets should be checked
	for ( int rowOffset = -1; rowOffset <= 1; ++rowOffset )
	{
		for ( int colOffset = -1; colOffset <= 1; ++colOffset )
		{
			if ( rowOffset != 0 && colOffset != 0 )
			{
				continue;
			}

			int rowIndex = playerRowIndex + rowOffset;
			int colIndex = playerColIndex + colOffset;

			if ( rowIndex < 0 || rowIndex >= GameConfig::TILE_ROWS ||
				colIndex < 0 || colIndex >= GameConfig::TILE_COLS )
			{
				continue;
			}

			auto pellet = m_allPellets[rowIndex][colIndex];

			if ( !pellet )
			{
				continue;
			}

			float dx = playerX - pellet->x;
			float dy = playerY - pellet->y;

			float distanceSqr = dx * dx + dy * dy;

			constexpr float width = GameConfig::TILE_WIDTH * 0.5f;
			constexpr float height = GameConfig::TILE_HEIGHT * 0.5f;
			constexpr float thresholdSqr = ( width * width ) + ( height * height );

			if ( distanceSqr <= thresholdSqr )
			{
				m_allPellets[rowIndex][colIndex] = nullptr;
				m_engine.destroyGameObject( pellet );

				ETileType tileType = m_tileMap.getTileType( rowIndex, colIndex );
				bool isPowerPellet = getPelletType( tileType ) == EPelletType::PowerPellet;

				auto it = std::find( m_powerPellets.begin(), m_powerPellets.end(), pellet );
				if ( it != m_powerPellets.end() )
				{
					m_powerPellets.erase( it );
				}

				PelletEatenEvent event { .isPowerPellet = isPowerPellet };
				m_engine.events().publish( event );
			}
		}
	}
}

void PelletManager::updatePowerPelletBlinking()
{
	bool active = static_cast<int>( m_engine.getTimeElapsed() / 0.2 ) % 2 == 0;

	for ( auto powerPellet : m_powerPellets )
	{
		powerPellet->setActive( active );
	}
}

PelletManager::EPelletType PelletManager::getPelletType( const ETileType tileType )
{
	switch ( tileType )
	{
		case ETileType::Junction_Pellet:
		case ETileType::Path_Pellet:
		{
			return EPelletType::Pellet;
		}

		case ETileType::Junction_PowerPellet:
		case ETileType::Path_PowerPellet:
		{
			return EPelletType::PowerPellet;
		}

		default:
			return EPelletType::NONE;
	}
}