#pragma once

class SparticleEngine;

class ScoreManager {
public:
	ScoreManager( SparticleEngine& engine );
	~ScoreManager();

private:
	SparticleEngine& m_engine;

	int m_currentScore = 0;
};