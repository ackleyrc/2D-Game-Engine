#pragma once

class SparticleEngine;
class GameObject;

class Component
{
public:
    virtual ~Component() = default;
    virtual void onUpdate( float deltaTime ) { }

protected:
    SparticleEngine& engine() const;
    GameObject* m_gameObject = nullptr;

private:
    friend class GameObject;
};