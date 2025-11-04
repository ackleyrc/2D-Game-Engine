#include "TileMap.h"
#include <stdexcept>
#include <ResourceManager.h>
#include <Sprite.h>
#include "ETileType.h"

TileMap::TileMap( ResourceManager& resources ) :
	m_resources( resources )
{ }

void TileMap::loadTileTypesFromFile( const std::string& path )
{
	auto& lines = m_resources.loadTextLines( path );

	m_tileTypes.clear();

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
					throw std::runtime_error( "Unrecognized Tile Type character: " + c );
			}
		}

		m_tileTypes.push_back( std::move( row ) );
	}
}

ETileType TileMap::getTileType( int rowIndex, int colIndex ) const
{
	if ( rowIndex < 0 || rowIndex >= static_cast<int>( m_tileTypes.size() ) ||
		colIndex < 0 || colIndex >= static_cast<int>( m_tileTypes[rowIndex].size() ) )
	{
		return ETileType::OutOfBounds;
	}

	return m_tileTypes[rowIndex][colIndex];
}

void TileMap::loadTileRotationsFromFile( const std::string& path )
{
	auto& lines = m_resources.loadTextLines( path );

	m_tileRotations.clear();

	for ( auto& line : lines )
	{
		std::vector<double> row;

		for ( char c : line )
		{
			switch ( c )
			{
				case ' ': continue;
				case '.': row.push_back( 0.0f ); break;
				case '0': row.push_back( 0.0f ); break;
				case '1': row.push_back( -90.0f ); break;
				case '2': row.push_back( -180.0f ); break;
				case '3': row.push_back( -270.0f ); break;
				default:
					throw std::runtime_error( "Unrecognized Tile Rotation character: " + c );
			}
		}

		m_tileRotations.push_back( std::move( row ) );
	}
}

double TileMap::getTileRotationDegrees( int rowIndex, int colIndex ) const
{
	return m_tileRotations.at( rowIndex ).at( colIndex );
}

Sprite TileMap::getSprite( const ETileType tileType ) const
{
	switch ( tileType )
	{
		case ETileType::Wall_00: return { "spritesheet", "level_a_thin_inner_corner" };
		case ETileType::Wall_01: return { "spritesheet", "level_a_thin_edge" };
		case ETileType::Wall_02: return { "spritesheet", "level_a_thick_outter_corner" };
		case ETileType::Wall_03: return { "spritesheet", "level_a_thick_edge" };
		case ETileType::Wall_04: return { "spritesheet", "level_a_cage_corner" };
		case ETileType::Wall_05: return { "spritesheet", "level_a_cage_edge" };
		case ETileType::Wall_06: return { "spritesheet", "level_a_thin_outter_corner" };
		case ETileType::Wall_07: return { "spritesheet", "level_a_thick_thin_left" };
		case ETileType::Wall_08: return { "spritesheet", "level_a_thick_thin_right" };
		case ETileType::Wall_09: return { "spritesheet", "level_a_thick_inner_corner" };
		case ETileType::GhostHomeGate: return { "spritesheet", "cage_gate" };
		default:
			throw std::runtime_error( "Unrecognized ETileType value" );
	}
}