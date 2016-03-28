#pragma once

#include "GameObject.h"

class PaddleComponent : public yam2d::Component, public yam2d::Updatable
{
public:
    PaddleComponent(yam2d::GameObject* p_owner);

    void update(float deltaTime);

    yam2d::GameObject* getGameObject() { return static_cast<yam2d::GameObject*>(getOwner()); }
    const yam2d::GameObject* getGameObject() const { return static_cast<const yam2d::GameObject*>(getOwner()); }
private:
    yam2d::vec2 m_position;
    float m_angle;
    float m_radius;
    bool m_moved;
};