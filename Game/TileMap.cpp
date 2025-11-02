#include "TileMap.h"
#include "ETileType.h"
#include <stdexcept>
#include <iostream>

TileMap::TileMap( ResourceManager& resources ) :
	m_resources( resources )
{ }

void TileMap::loadFromFile( const std::string& path )
{
	auto& lines = m_resources.loadTextLines( path );

	m_tiles.clear();

	for ( auto& line : lines )
	{
		std::vector<ETileType> row;

		for ( char c : line )
		{
			switch ( c )
			{
				case ' ': continue;
				case 'X': row.push_back( ETileType::Empty ); break;
				case '0': row.push_back( ETileType::Wall_00 ); break;
				case '1': row.push_back( ETileType::Wall_01 ); break;
				case '2': row.push_back( ETileType::Wall_02 ); break;
				case '3': row.push_back( ETileType::Wall_03 ); break;
				case '4': row.push_back( ETileType::Wall_04 ); break;
				case '5': row.push_back( ETileType::Wall_05 ); break;
				case '6': row.push_back( ETileType::Wall_06 ); break;
				case '7': row.push_back( ETileType::Wall_07 ); break;
				case '8': row.push_back( ETileType::Wall_08 ); break;
				case '9': row.push_back( ETileType::Wall_09 ); break;
				case '+': row.push_back( ETileType::Junction_Pellet ); break;
				case 'P': row.push_back( ETileType::Junction_PowerPellet ); break;
				case 'n': row.push_back( ETileType::Junction_Empty ); break;
				case '.': row.push_back( ETileType::Path_Pellet ); break;
				case 'p': row.push_back( ETileType::Path_PowerPellet ); break;
				case '|': row.push_back( ETileType::Path_Empty_Vertical ); break;
				case '-': row.push_back( ETileType::Path_Empty_Horizontal ); break;
				case '=': row.push_back( ETileType::GhostHomeGate ); break;
				default:
					throw std::runtime_error( "Unrecognized ETileType value" );
			}
		}

		m_tiles.push_back( std::move( row ) );
	}
}

ETileType TileMap::getTileType( int rowIndex, int colIndex ) const
{
	if ( rowIndex < 0 || rowIndex >= static_cast<int>( m_tiles.size() ) ||
		colIndex < 0 || colIndex >= static_cast<int>( m_tiles[rowIndex].size() ) )
	{
		return ETileType::OutOfBounds;
	}

	return m_tiles[rowIndex][colIndex];
}