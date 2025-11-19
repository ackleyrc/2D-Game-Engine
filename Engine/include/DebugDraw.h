#pragma once
#include <vector>
#include "Vector.h"
#include "Color.h"

class SparticleEngine;

struct DebugLine 
{
	Vector2f startPosition;
	Vector2f endPosition;
	Color color;
};

class DebugDraw
{
public:
	void setEnabled( bool enabled );
	void drawLine( const Vector2f& start, const Vector2f& end, const Color& color );

private:
	friend class SparticleEngine;

	bool m_isEnabled = false;
	std::vector<DebugLine> m_lines;
};