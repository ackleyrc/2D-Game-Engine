#pragma once
#include <vector>
#include <string>
#include "ResourceManager.h"

class TileMap 
{
public:
	TileMap( ResourceManager& resources );

	void loadFromFile( const std::string& path );
	
private:
	ResourceManager& m_resources;
};