#pragma once
#include "EngineAPI.h"

class SparticleEngine;
class GameObject;

class SPARTICLE_API Component
{
public:
    virtual ~Component() = default;
    virtual void onUpdate( float deltaTime ) { }
    virtual void onAdd() { }
    void setActive( bool active ) { m_isActive = active; }

protected:
    SparticleEngine& engine() const;
    GameObject* m_gameObject = nullptr;
    bool m_isActive = true;

private:
    friend class GameObject;
    void update( float deltaTime );
    void add();
};