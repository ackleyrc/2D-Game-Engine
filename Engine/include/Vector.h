#pragma once
#include <string>
#include "EngineAPI.h"

class SPARTICLE_API Vector2f;
class SPARTICLE_API Vector2i;

class SPARTICLE_API Vector2f {
public:
	float x;
	float y;

	Vector2f() noexcept;
	Vector2f( float x_, float y_ ) noexcept;
	explicit Vector2f( const Vector2i& vi ) noexcept;

	Vector2f( const Vector2f& ) noexcept = default;
	Vector2f( Vector2f&& ) noexcept = default;
	Vector2f& operator=( const Vector2f& ) noexcept = default;
	Vector2f& operator=( Vector2f&& ) noexcept = default;

	Vector2f operator+( const Vector2f& other ) const;
	Vector2f operator-( const Vector2f& other ) const;
	Vector2f operator*( float scalar ) const;
	Vector2f operator/( float scalar ) const;

	Vector2f& operator+=( const Vector2f& other );
	Vector2f& operator-=( const Vector2f& other );
	Vector2f& operator*=( float scalar );
	Vector2f& operator/=( float scalar );

	bool operator==( const Vector2f& other ) const noexcept;
	bool operator!=( const Vector2f& other ) const noexcept;

	double length() const;
	double lengthSqr() const noexcept;
	Vector2f normalized() const;
	std::string toString() const;
};

SPARTICLE_API Vector2f operator*( float scalar, Vector2f& v );

class SPARTICLE_API Vector2i {
public:
	int x;
	int y;

	Vector2i() noexcept;
	Vector2i( int x_, int y_ ) noexcept;
	explicit Vector2i( const Vector2f& vf ) noexcept;

	Vector2i( const Vector2i& ) noexcept = default;
	Vector2i( Vector2i&& ) noexcept = default;
	Vector2i& operator=( const Vector2i& ) noexcept = default;
	Vector2i& operator=( Vector2i&& ) noexcept = default;

	Vector2i operator+( const Vector2i& other ) const;
	Vector2i operator-( const Vector2i& other ) const;

	Vector2i& operator+=( const Vector2i& other );
	Vector2i& operator-=( const Vector2i& other );

	bool operator==( const Vector2i& other ) const noexcept;
	bool operator!=( const Vector2i& other ) const noexcept;

	double length() const;
	double lengthSqr() const noexcept;
	Vector2i normalized() const;
	std::string toString() const;
};

SPARTICLE_API float dot( const Vector2f& a, const Vector2f& b );
SPARTICLE_API double distance( const Vector2f& a, const Vector2f& b );
SPARTICLE_API Vector2f lerp( const Vector2f& a, const Vector2f& b, float t );
SPARTICLE_API Vector2f clampLength( const Vector2f& v, float maxLength );

SPARTICLE_API int manhattanDistance( const Vector2i& a, const Vector2i& b );
SPARTICLE_API double euclideanDistance( const Vector2i& a, const Vector2i& b );