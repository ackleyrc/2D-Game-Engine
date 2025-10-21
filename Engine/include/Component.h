#pragma once

class GameObject;

class Component
{
public:
    virtual ~Component() = default;
    virtual void onUpdate( float deltaTime ) { }

protected:
    GameObject* m_gameObject = nullptr;

private:
    friend class GameObject;
};