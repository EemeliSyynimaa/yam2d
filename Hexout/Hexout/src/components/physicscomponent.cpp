#include "components/physicscomponent.h"

#include "core/b2util.h"

PhysicsComponent::PhysicsComponent(yam2d::GameObject* p_owner, b2World* p_world, b2Body* p_body) :
	Component(p_owner, Component::getDefaultProperties()), m_world(p_world), m_body(p_body)
{
}

PhysicsComponent::~PhysicsComponent()
{
	m_world->DestroyBody(m_body);
}

void PhysicsComponent::update(float deltaTime)
{
	getGameObject()->setPosition(box2DToWorld(m_body->GetPosition()));
	getGameObject()->setRotation(m_body->GetAngle());
}