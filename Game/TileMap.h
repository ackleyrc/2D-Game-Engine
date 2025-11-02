#pragma once
#include <vector>
#include <string>
#include "ResourceManager.h"

enum class ETileType;
struct Sprite;

class TileMap 
{
public:
	TileMap( ResourceManager& resources );

	void loadTileTypesFromFile( const std::string& path );
	void loadTileRotationsFromFile( const std::string& path );

	ETileType getTileType( int rowIndex, int colIndex ) const;
	double getTileRotationDegrees( int rowIndex, int colIndex ) const;

	Sprite getSprite( const ETileType ) const;
	
private:
	ResourceManager& m_resources;
	std::vector<std::vector<ETileType>> m_tileTypes;
	std::vector<std::vector<double>> m_tileRotations;
};