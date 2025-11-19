#include "DebugDraw.h"

void DebugDraw::setEnabled( bool enabled )
{
	m_isEnabled = enabled;
}

void DebugDraw::drawLine( const Vector2f& start, const Vector2f& end, const Color& color )
{
	m_lines.push_back( { start, end, color } );
}