#include "VectorImpl.h"
#include "Vector.h"
#include <cmath>

using namespace VectorImpl;

Vector2f::Vector2f() noexcept : x( 0.0f ), y( 0.0f ) { }
Vector2f::Vector2f( float x_, float y_ ) noexcept : x( x_ ), y( y_ ) { }
Vector2f::Vector2f( const Vector2i& vi ) noexcept : x( static_cast<float>( vi.x ) ), y( static_cast<float>( vi.y ) ) { }

Vector2f Vector2f::operator+( const Vector2f& other ) const
{
	Vector2<float> a { x , y }, b { other.x, other.y };
	auto r = a + b;
	return Vector2f { static_cast<float>( r.x ), static_cast<float>( r.y ) };
}

Vector2f Vector2f::operator-( const Vector2f& other ) const
{
	Vector2<float> a { x , y }, b { other.x, other.y };
	auto r = a - b;
	return Vector2f { static_cast<float>( r.x ), static_cast<float>( r.y ) };
}

Vector2f Vector2f::operator*( float scalar ) const
{
	Vector2<float> a { x,y };
	auto r = a * scalar;
	return Vector2f { static_cast<float>( r.x ), static_cast<float>( r.y ) };
}

Vector2f Vector2f::operator/( float scalar ) const
{
	Vector2<float> a { x,y };
	auto r = a / scalar;
	return Vector2f { static_cast<float>( r.x ), static_cast<float>( r.y ) };
}

Vector2f& Vector2f::operator+=( const Vector2f& other )
{
	Vector2<float> a { x,y }, b { other.x, other.y };
	a += b;
	x = static_cast<float>( a.x ); y = static_cast<float>( a.y );
	return *this;
}

Vector2f& Vector2f::operator-=( const Vector2f& other )
{
	Vector2<float> a { x,y }, b { other.x, other.y };
	a -= b;
	x = static_cast<float>( a.x ); y = static_cast<float>( a.y );
	return *this;
}

Vector2f& Vector2f::operator*=( float scalar )
{
	Vector2<float> a { x,y };
	a *= scalar;
	x = static_cast<float>( a.x ); y = static_cast<float>( a.y );
	return *this;
}

Vector2f& Vector2f::operator/=( float scalar )
{
	Vector2<float> a { x,y };
	a /= scalar;
	x = static_cast<float>( a.x ); y = static_cast<float>( a.y );
	return *this;
}

bool Vector2f::operator==( const Vector2f& other ) const noexcept
{
	return x == other.x && y == other.y;
}

bool Vector2f::operator!=( const Vector2f& other ) const noexcept { return !( *this == other ); }

double Vector2f::length() const { Vector2<float> a { x,y }; return a.length(); }
double Vector2f::lengthSqr() const noexcept { Vector2<float> a { x,y }; return a.lengthSqr(); }
Vector2f Vector2f::normalized() const { Vector2<float> a { x,y }; auto r = a.normalized(); return { static_cast<float>( r.x ), static_cast<float>( r.y ) }; }
std::string Vector2f::toString() const { Vector2<float> a { x,y }; return a.toString(); }

Vector2f operator*( float scalar, const Vector2f& v )
{
	return v * scalar;
}



Vector2i::Vector2i() noexcept : x( 0 ), y( 0 ) { }
Vector2i::Vector2i( int x_, int y_ ) noexcept : x( x_ ), y( y_ ) { }
Vector2i::Vector2i( const Vector2f& vf ) noexcept : x( static_cast<int>( vf.x ) ), y( static_cast<int>( vf.y ) ) { }

Vector2i Vector2i::operator+( const Vector2i& other ) const
{
	Vector2<int> a { x , y }, b { other.x, other.y };
	auto r = a + b;
	return Vector2i { static_cast<int>( r.x ), static_cast<int>( r.y ) };
}

Vector2i Vector2i::operator-( const Vector2i& other ) const
{
	Vector2<int> a { x , y }, b { other.x, other.y };
	auto r = a - b;
	return Vector2i { static_cast<int>( r.x ), static_cast<int>( r.y ) };
}

Vector2i& Vector2i::operator+=( const Vector2i& other )
{
	Vector2<int> a { x,y }, b { other.x, other.y };
	a += b;
	x = static_cast<int>( a.x ); y = static_cast<int>( a.y );
	return *this;
}

Vector2i& Vector2i::operator-=( const Vector2i& other )
{
	Vector2<int> a { x,y }, b { other.x, other.y };
	a -= b;
	x = static_cast<int>( a.x ); y = static_cast<int>( a.y );
	return *this;
}

bool Vector2i::operator==( const Vector2i& other ) const noexcept { return x == other.x && y == other.y; }
bool Vector2i::operator!=( const Vector2i& other ) const noexcept { return !( *this == other ); }

std::string Vector2i::toString() const { Vector2<int> a { x,y }; return a.toString(); }


float dot( const Vector2f& a, const Vector2f& b )
{
	Vector2<float> A { a.x,a.y }, B { b.x,b.y };
	return static_cast<float>( VectorImpl::dot( A, B ) );
}

double distance( const Vector2f& a, const Vector2f& b )
{
	Vector2<float> A { a.x,a.y }, B { b.x,b.y };
	return VectorImpl::distance( A, B );
}

Vector2f lerp( const Vector2f& a, const Vector2f& b, float t )
{
	auto r = VectorImpl::lerp( Vector2<float>{a.x, a.y}, Vector2<float>{b.x, b.y}, t );
	return Vector2f { static_cast<float>( r.x ), static_cast<float>( r.y ) };
}

Vector2f clampLength( const Vector2f& v, float maxLen )
{
	Vector2<float> V { v.x, v.y };
	double len = V.length();
	if ( len <= maxLen ) return v;
	auto r = V * static_cast<float>( maxLen / len );
	return Vector2f { static_cast<float>( r.x ), static_cast<float>( r.y ) };
}

int manhattanDistance( const Vector2i& a, const Vector2i& b )
{
	return std::abs( a.x - b.x ) + std::abs( a.y - b.y );
}

double euclideanDistance( const Vector2i& a, const Vector2i& b )
{
	Vector2<int> A { a.x,a.y }, B { b.x,b.y };
	return VectorImpl::distance( A, B );
}

namespace VectorImpl
{
	template struct Vector2<int>;
	template struct Vector2<float>;
}