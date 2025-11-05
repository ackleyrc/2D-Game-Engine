#include "ScoreManager.h"
#include <SparticleEngine.h>
#include "GameEvents.h"

ScoreManager::ScoreManager( SparticleEngine& engine ) : 
	m_engine( engine ) 
{
	m_engine.events().subscribe<PelletEatenEvent>(
		[this] ( const PelletEatenEvent& event )
		{
			m_currentScore += event.isPowerPellet ? 50 : 10;
		}
	);
}

ScoreManager::~ScoreManager() = default;