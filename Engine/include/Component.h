#pragma once
#include "EngineAPI.h"

class SparticleEngine;
class GameObject;

class SPARTICLE_API Component
{
public:
    virtual ~Component() = default;
    virtual void onUpdate( const float deltaTime ) { }
    virtual void onAdd() { }
    void setEnabled( bool enabled ) { m_isEnabled = enabled; }
    bool isEnabled() { return m_isEnabled; }
    GameObject* getGameObject() const { return m_gameObject; }

protected:
    SparticleEngine& engine() const;
    GameObject* m_gameObject = nullptr;
    bool m_isEnabled = true;

private:
    friend class GameObject;
    void update( float deltaTime );
    void add();
};