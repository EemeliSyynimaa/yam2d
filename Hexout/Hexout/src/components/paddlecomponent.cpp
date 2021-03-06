#include "components/paddlecomponent.h"
#include "components/physicscomponent.h"

#include "Input.h"
#include "vec2.h"
#include "slm/mat4.h"
#include "slm/quat.h"
#include "Box2D/Box2D.h"
#include "GameObject.h"

#include <iostream>

PaddleComponent::PaddleComponent(yam2d::GameObject* p_owner, yam2d::TmxMap* p_map) :
    Component(p_owner, Component::getDefaultProperties()), 
    m_origin(0.0f),
    m_speed(0.75f), 
    m_radius(8.0f),
    m_angle(0.0f),
    m_screenW(0.0f),
    m_screenH(0.0f),
    m_map(p_map)
{
    m_origin = m_map->findGameObjectByName("origin")->getPosition();
}

void PaddleComponent::setScreenSize(int x, int y)
{
    m_screenW = x / 2.0f;
    m_screenH = y / 2.0f;
}

void PaddleComponent::update(float deltaTime)
{
    b2Vec2 position;
    position.x = yam2d::getMouseAxisX() - m_screenW;
    position.y = yam2d::getMouseAxisY() - m_screenH;

    if (position.Length() > 0)
    {
        m_angle = acosf(position.x / position.Length());

        if (position.y < 0) m_angle *= -1;
    }
     
    position.Normalize();

    getGameObject()->getComponent<PhysicsComponent>()->getBody()->SetTransform(m_radius * position + m_origin, m_angle);
}