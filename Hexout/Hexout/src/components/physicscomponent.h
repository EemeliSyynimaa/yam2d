#pragma once

#include "GameObject.h"
#include "Box2D/Box2D.h"

class PhysicsComponent : public yam2d::Component, public yam2d::Updatable
{
public:
	PhysicsComponent(yam2d::GameObject* p_owner, b2World* p_world, b2Body* p_body);
	~PhysicsComponent();

	void update(float deltaTime);

	yam2d::GameObject* getGameObject() { return static_cast<yam2d::GameObject*>(getOwner()); }
	const yam2d::GameObject* getGameObject() const { return static_cast<const yam2d::GameObject*>(getOwner()); }
private:

	b2Body* m_body;
	yam2d::Ref<b2World> m_world;
};