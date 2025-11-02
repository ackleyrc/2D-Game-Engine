#pragma once
#include <cmath>
#include <algorithm>

namespace spmath
{
	inline bool nearlyEqual( float a, float b, float epsilon = 1e-5f )
	{
		return std::fabs( a - b ) <= epsilon * std::max( 1.0f, std::max( std::fabs( a ), std::fabs( b ) ) );
	}

	inline bool nearlyEqual( double a, double b, double epsilon = 1e-9f )
	{
		return std::fabs( a - b ) <= epsilon * std::max( 1.0, std::max( std::fabs( a ), std::fabs( b ) ) );
	}
}