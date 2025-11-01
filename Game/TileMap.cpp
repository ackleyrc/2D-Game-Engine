#include "TileMap.h"
#include <iostream>

TileMap::TileMap( ResourceManager& resources ) :
	m_resources( resources )
{ }

void TileMap::loadFromFile( const std::string& path )
{
	auto lines = m_resources.loadTextLines( path );

	for ( auto& line : lines )
	{
		// TODO: Convert each character into TileTypes in a grid
		std::cout << line << std::endl;
	}
}