#pragma once

#include "GameObject.h"
#include "Box2D/Box2D.h"

class PhysicsComponent;

class BallComponent : public yam2d::Component, public yam2d::Updatable
{
public:
    BallComponent(yam2d::GameObject* p_owner, const yam2d::vec2& origin);

    void update(float deltaTime);
    void speedUp(float amount);
    void setScreenSize(int x, int y);

    yam2d::GameObject* getGameObject() { return static_cast<yam2d::GameObject*>(getOwner()); }
    const yam2d::GameObject* getGameObject() const { return static_cast<const yam2d::GameObject*>(getOwner()); }
private:
    b2Vec2 m_origin;
    float m_speed;
    float m_radius;
    float m_screenW;
    float m_screenH;
    float m_angle;
    bool m_launched;
    b2Body* m_body;
};