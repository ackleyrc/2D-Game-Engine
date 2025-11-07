#pragma once
#include <array>

enum class EDirection { 
	NONE, 
	Up, 
	Left, 
	Down, 
	Right,
};

namespace DirectionUtils
{
	inline constexpr std::array<EDirection, 4> directions = {
		EDirection::Up,
		EDirection::Left,
		EDirection::Down,
		EDirection::Right
	};

	inline EDirection getOpposite( EDirection direction )
	{
		switch ( direction )
		{
			case EDirection::Up:		return EDirection::Down;
			case EDirection::Down:		return EDirection::Up;
			case EDirection::Left:		return EDirection::Right;
			case EDirection::Right:		return EDirection::Left;
			default:					return EDirection::NONE;
		}
	}
}