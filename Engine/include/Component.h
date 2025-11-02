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

protected:
    SparticleEngine& engine() const;
    GameObject* m_gameObject = nullptr;

private:
    friend class GameObject;
    void update( float deltaTime );
    void add();
};