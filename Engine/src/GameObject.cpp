#include "GameObject.h"
#include "SparticleEngine.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Component.h"

void GameObject::update( float deltaTime )
{
	for ( auto& component : m_components )
	{
		component->update( deltaTime );
	}
}

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