#pragma once
#include <vector>
#include <string>
#include <SparticleEngine.h>

class ResourceManager;
enum class ETileType;
enum class EDirection;
struct Sprite;

class TileMap 
{
public:
	TileMap( ResourceManager& resources );

	void loadTileTypesFromFile( const std::string& path );
	void loadTileRotationsFromFile( const std::string& path );

	ETileType getTileTypeForPosition( Vector2f position ) const;
	ETileType getTileTypeForRowCol( int rowIndex, int colIndex ) const;
	double getTileRotationDegrees( int rowIndex, int colIndex ) const;

	int getTileColIndex( float x ) const;
	int getTileRowIndex( float y ) const;
	Vector2f getTilePositionAt( int rowIndex, int colIndex ) const;
	Vector2f getTilePositionFrom( int rowIndex, int colIndex, EDirection direction ) const;

	Sprite getSprite( const ETileType ) const;
	
private:
	ResourceManager& m_resources;
	std::vector<std::vector<ETileType>> m_tileTypes;
	std::vector<std::vector<double>> m_tileRotations;
};