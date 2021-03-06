#pragma once

#include "GameObject.h"
#include "Box2D/Box2D.h"
#include "Map.h"

class PaddleComponent : public yam2d::Component, public yam2d::Updatable
{
public:
    PaddleComponent(yam2d::GameObject* p_owner, yam2d::TmxMap* p_map);

    void update(float deltaTime);
    void setScreenSize(int x, int y);

    yam2d::GameObject* getGameObject() { return static_cast<yam2d::GameObject*>(getOwner()); }
    const yam2d::GameObject* getGameObject() const { return static_cast<const yam2d::GameObject*>(getOwner()); }
private:
    b2Vec2 m_origin;
    float m_speed;
    float m_radius;
    float m_angle;
    float m_screenW;
    float m_screenH;
    yam2d::TmxMap* m_map;
};