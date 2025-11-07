#pragma once

enum class EDirection;
enum class ETileType;
class TileMap;

class IMovementController {
public:
	virtual ~IMovementController() = default;

	virtual EDirection updateDesiredDirection( float x, float y ) = 0;
	virtual bool isWalkable( const ETileType tileType ) const = 0;
};