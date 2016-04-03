#include "components/paddlecomponent.h"
#include "Input.h"
#include "vec2.h"
#include "slm/mat4.h"
#include "slm/quat.h"

#include "Box2D/Box2D.h"
#include "components/physicscomponent.h"
#include "GameObject.h"

#include <iostream>

PaddleComponent::PaddleComponent(yam2d::GameObject* p_owner) :
Component(p_owner, Component::getDefaultProperties()), m_speed(0.75f), m_origin(0.0f, 0.0f), m_radius(8.0f), m_angle(0.0f), m_moved(true)
    {
}

void PaddleComponent::setOrigin(const yam2d::vec2& position)
{
    m_origin = position;
}

void PaddleComponent::update(float deltaTime)
{
    b2Vec2 position;
    position.x = yam2d::getMouseAxisX() - 640.0f;
    position.y = yam2d::getMouseAxisY() - 360.0f;

    if (position.Length() > 0)
    {
        m_angle = acosf(position.x / position.Length());

        if (position.y < 0) m_angle *= -1;
    }
     
    position.Normalize();
    position = m_radius * position + m_origin;

    getGameObject()->getComponent<PhysicsComponent>()->getBody()->SetTransform(position, m_angle);
}