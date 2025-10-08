#pragma once
#include <string>
#include <memory>

// forward declaration
class SparticleEngine;

class GameObject
{
public:
	GameObject( SparticleEngine* engine );
	virtual ~GameObject() = default;

	// Transform
	float x = 0.0f;
	float y = 0.0f;

	//std::string spriteID;

	virtual void onUpdate( float deltaTime );

private:
	friend class SparticleEngine;
	SparticleEngine* m_engine = nullptr;
};