#include "Component.h"
#include "SparticleEngine.h"

SparticleEngine& Component::engine() const
{
	return m_gameObject->engine();
}