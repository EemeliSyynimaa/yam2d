#include "components/physicscomponent.h"

#include "Box2D/Box2D.h"

PhysicsComponent::PhysicsComponent(yam2d::GameObject* p_owner, b2World* p_world, const b2BodyDef& p_bodyDef) :
	Component(p_owner, Component::getDefaultProperties())
{
	m_body = p_world->CreateBody(&p_bodyDef);
}

void PhysicsComponent::update(float deltaTime)
{

}