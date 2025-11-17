#pragma once
#include <type_traits>
#include <cmath>
#include <ostream>
#include <sstream>
#include "EngineAPI.h"

namespace VectorImpl
{
	template <typename T>
	struct SPARTICLE_API Vector2 {
		static_assert( std::is_arithmetic_v<T>, "Vector2 requires an arithmetic type" );

		T x {};
		T y {};

		constexpr Vector2() noexcept = default;
		constexpr Vector2( T x_, T y_ ) noexcept : x( x_ ), y( y_ ) { }

		template<typename U>
		explicit constexpr Vector2( const Vector2<U>& other ) noexcept
			: x( static_cast<T>( other.x ) ), y( static_cast<T>( other.y ) )
		{ }

		constexpr Vector2 operator+( const Vector2& other ) const noexcept { return { T( x + other.x ), T( y + other.y ) }; }
		constexpr Vector2 operator-( const Vector2& other ) const noexcept { return { T( x - other.x ), T( y - other.y ) }; }
		constexpr Vector2 operator*( T scalar ) const noexcept { return { T( x * scalar ), T( y * scalar ) }; }
		constexpr Vector2 operator/( T scalar ) const noexcept { return { T( x / scalar ), T( y / scalar ) }; }

		constexpr Vector2& operator+=( const Vector2& other ) noexcept { x += other.x; y += other.y; return *this; }
		constexpr Vector2& operator-=( const Vector2& other ) noexcept { x -= other.x; y -= other.y; return *this; }
		constexpr Vector2& operator*=( T scalar ) { x *= scalar; y *= scalar; return *this; }
		constexpr Vector2& operator/=( T scalar ) { x /= scalar; y /= scalar; return *this; }

		constexpr bool operator==( const Vector2& other ) const noexcept { return x == other.x && y == other.y; }
		constexpr bool operator!=( const Vector2& other ) const noexcept { return !( *this == other ); }

		constexpr double lengthSqr() const noexcept
		{
			return static_cast<double>( x ) * static_cast<double>( x ) + static_cast<double>( y ) * static_cast<double>( y );
		}

		double length() const noexcept { return std::sqrt( lengthSqr() ); }

		Vector2 normalized() const
		{
			double len = length();
			if ( len == 0.0 ) return *this;
			T inv = static_cast<T>( 1.0 / len );
			return { T( x * inv ), T( y * inv ) };
		}

		std::string toString() const
		{
			std::ostringstream stream;
			stream << "(" << x << ", " << y << ")";
			return stream.str();
		}
	};

	template<typename T, typename U>
	constexpr auto add( const Vector2<T>& a, const Vector2<U>& b )
	{
		using R = std::common_type_t<T, U>;
		return Vector2<R>{ static_cast<R>( a.x ) + static_cast<R>( b.x ), static_cast<R>( a.y ) + static_cast<R>( b.y ) };
	}

	template<typename T, typename U>
	constexpr auto sub( const Vector2<T>& a, const Vector2<U>& b )
	{
		using R = std::common_type_t<T, U>;
		return Vector2<R>{ static_cast<R>( a.x ) - static_cast<R>( b.x ), static_cast<R>( a.y ) - static_cast<R>( b.y ) };
	}

	template<typename T, typename U>
	constexpr auto dot( const Vector2<T>& a, const Vector2<U>& b )
	{
		using R = std::common_type_t<T, U>;
		return static_cast<R>( a.x ) * static_cast<R>( b.x ) + static_cast<R>( a.y ) * static_cast<R>( b.y );
	}

	template<typename T, typename U>
	double distance( const Vector2<T>& a, const Vector2<U>& b )
	{
		return sub( a, b ).length();
	}

	template<typename T>
	Vector2<T> lerp( const Vector2<T>& a, const Vector2<T>& b, double t )
	{
		using R = T;
		return Vector2<R>{
			static_cast<R>( a.x + ( b.x - a.x ) * t ),
			static_cast<R>( a.y + ( b.y - a.y ) * t )
		};
	}
}