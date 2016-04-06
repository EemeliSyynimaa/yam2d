#include "components/ballcomponent.h"
#include "components/physicscomponent.h"
#include "components/paddlecomponent.h"

#include "Input.h"

BallComponent::BallComponent(yam2d::GameObject* p_owner, yam2d::TmxMap* p_map) :
    Component(p_owner, Component::getDefaultProperties()), 
    m_origin(0.0f),
    m_speed(192.0f),
    m_radius(7.4f),
    m_screenW(0.0f),
    m_screenH(0.0f),
    m_angle(0.0f),
    m_launched(false),
    m_dead(false),
    m_body(nullptr),
    m_map(p_map)
{
    m_body = getOwner()->getComponent<PhysicsComponent>()->getBody();
    m_origin = m_map->findGameObjectByName("origin")->getPosition();
    assert(m_body);
}

void BallComponent::update(float deltaTime)
{
    if (m_launched)
    {
        b2Vec2 direction = m_body->GetLinearVelocity();
        direction.Normalize();

        m_body->SetLinearVelocity(m_speed * deltaTime * direction);

        b2Vec2 distance = getGameObject()->getPosition() - m_origin;

        if (distance.Length() > 10.0f)
        {
            m_dead = true;
            m_body->SetLinearVelocity(b2Vec2(0.0f));
            m_body->SetType(b2_kinematicBody);
        }
    }
    else if (yam2d::isMouseButtonPressed(yam2d::MOUSE_LEFT))
    {
        m_body->SetType(b2_dynamicBody);
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

bool BallComponent::isDead()
{
    return m_dead;
}

void BallComponent::revive()
{
    m_dead = false;
    m_launched = false;
}