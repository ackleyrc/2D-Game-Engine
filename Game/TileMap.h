#pragma once
#include <vector>
#include <string>
#include "ResourceManager.h"

enum class ETileType;

class TileMap 
{
public:
	TileMap( ResourceManager& resources );

	void loadFromFile( const std::string& path );

	ETileType getTileType( int rowIndex, int colIndex ) const;
	
private:
	ResourceManager& m_resources;
	std::vector<std::vector<ETileType>> m_tiles;
};