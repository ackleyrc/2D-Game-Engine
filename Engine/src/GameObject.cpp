#include "GameObject.h"
#include "SparticleEngine.h"
#include "ResourceManager.h"
#include "InputManager.h"

GameObject::GameObject( SparticleEngine* engine ) : m_engine( engine ) 
{ }

void GameObject::onUpdate( float deltaTime )
{ }

SparticleEngine& GameObject::engine() const
{
	return *m_engine;
}

ResourceManager& GameObject::resources() const
{
	return m_engine->resources();
}

InputManager& GameObject::input() const
{
	return m_engine->input();
}