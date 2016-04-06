#include "components/physicscomponent.h"

#include <iostream>

PhysicsComponent::PhysicsComponent(yam2d::GameObject* p_owner, b2World* p_world, b2Body* p_body) :
	Component(p_owner, Component::getDefaultProperties()), 
    m_body(p_body),
    m_world(p_world)
{
}

PhysicsComponent::~PhysicsComponent()
{
	m_world->DestroyBody(m_body);
}

void PhysicsComponent::update(float deltaTime)
{
    if (m_body->GetType() != b2_staticBody)
    {
        getGameObject()->setPosition(m_body->GetTransform().p.x, m_body->GetTransform().p.y);
        getGameObject()->setRotation(m_body->GetTransform().q.GetAngle());
    }
}