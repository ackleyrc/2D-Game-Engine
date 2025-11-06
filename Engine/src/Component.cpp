#include "Component.h"
#include "SparticleEngine.h"
#include "EngineInternalUtils.h"

SparticleEngine& Component::engine() const
{
	return m_gameObject->engine();
}

void Component::add()
{
	if ( !safeCall( "Component::onAdd", [this] () { this->onAdd(); } ) )
	{
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Component failed on add." );
		throw std::runtime_error( "Component failed on add." );
	}
}

void Component::update( const float deltaTime )
{
	if ( !m_isEnabled )
	{
		return;
	}

	if ( !safeCall( "Component::onUpdate", [this, deltaTime] () { this->onUpdate( deltaTime ); } ) )
	{
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Component failed to update." );
		throw std::runtime_error( "Component failed to update." );
	}
}