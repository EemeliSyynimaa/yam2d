#include "components/ballcomponent.h"
#include "components/physicscomponent.h"
#include "components/paddlecomponent.h"

#include "Input.h"

BallComponent::BallComponent(yam2d::GameObject* p_owner, const yam2d::vec2& origin) :
Component(p_owner, Component::getDefaultProperties()), m_origin(origin), m_launched(false), m_speed(192.0f), m_radius(7.5f), m_angle(0.0f)
{
    m_body = getOwner()->getComponent<PhysicsComponent>()->getBody();

    assert(m_body);
}

void BallComponent::update(float deltaTime)
{
    if (m_launched)
    {
        b2Vec2 direction = m_body->GetLinearVelocity();
        direction.Normalize();

        m_body->SetLinearVelocity(m_speed * deltaTime * direction);
    }
    else if (yam2d::isMouseButtonPressed(yam2d::MOUSE_LEFT))
    {
        b2Vec2 direction(cos(m_angle) * m_radius, sin(m_angle) * m_radius);
        direction.Normalize();

        m_body->ApplyForceToCenter(-5.0f * direction);
        m_launched = true;
    }
    else
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
        position = m_radius * position + m_origin;

        getGameObject()->getComponent<PhysicsComponent>()->getBody()->SetTransform(position, m_angle);
    }
}

void BallComponent::speedUp(float amount)
{
    m_speed += amount;
}

void BallComponent::setScreenSize(int x, int y)
{
    m_screenW = x / 2.0f;
    m_screenH = y / 2.0f;
}