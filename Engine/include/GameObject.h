#pragma once
#include <string>
#include <memory>
#include <vector>
#include "EngineAPI.h"

class SparticleEngine;
class ResourceManager;
class InputManager;
class Component;

class SPARTICLE_API GameObject
{
public:
	GameObject( SparticleEngine* engine );
	~GameObject();

	GameObject( const GameObject& ) = delete;
	GameObject& operator=( const GameObject& ) = delete;

	// Transform
	float x = 0.0f;
	float y = 0.0f;

	void onUpdate( float deltaTime );

	template<typename T, typename... Args>
	T& addComponent( Args&&... args )
	{
		static_assert( std::is_base_of_v<Component, T>, "T must derive from Component" );
		auto component = std::make_unique<T>( std::forward<Args>( args )... );
		component->m_gameObject = this;
		T& ref = *component;
		m_components.push_back( std::move( component ) );
		return ref;
	}

	template<typename T>
	T* getComponent()
	{
		static_assert( std::is_base_of_v<Component, T>, "T must derive from Component" );
		for ( auto& component : m_components )
		{
			if ( auto* casted = dynamic_cast<T*>( component.get() ) )
			{
				return casted;
			}
		}
		return nullptr;
	}

	SparticleEngine& engine() const;

protected:
	ResourceManager& resources() const;
	InputManager& input() const;

private:
	friend class SparticleEngine;
	SparticleEngine* m_engine = nullptr;
	std::vector<std::unique_ptr<Component>> m_components;
};