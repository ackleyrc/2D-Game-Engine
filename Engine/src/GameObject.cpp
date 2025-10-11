#include "GameObject.h"
#include "SparticleEngine.h"

GameObject::GameObject( SparticleEngine* engine ) : m_engine( engine ) 
{ }

void GameObject::onUpdate( float deltaTime )
{
	// TEMP player logic
	const float playerSpeed = 100.0f;

	float horizontalAxis = m_engine->getInput().getAxisHorizontal();
	float verticalAxis = m_engine->getInput().getAxisVertical();

	x += ( horizontalAxis * playerSpeed * deltaTime );
	y += ( verticalAxis * playerSpeed * deltaTime );
}