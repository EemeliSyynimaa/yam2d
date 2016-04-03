#pragma once

#include "GameObject.h"
#include "Box2D/Box2D.h"

class PaddleComponent : public yam2d::Component, public yam2d::Updatable
{
public:
    PaddleComponent(yam2d::GameObject* p_owner);

    void update(float deltaTime);
    void setOrigin(const yam2d::vec2& position);

    yam2d::GameObject* getGameObject() { return static_cast<yam2d::GameObject*>(getOwner()); }
    const yam2d::GameObject* getGameObject() const { return static_cast<const yam2d::GameObject*>(getOwner()); }
private:
    b2Vec2 m_origin;
    float m_speed;
    float m_radius;
    float m_angle;
    int m_mouseX;
    bool m_moved;
};