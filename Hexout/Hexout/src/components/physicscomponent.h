#pragma once

#include "GameObject.h"

class b2World;
class b2Body;
struct b2BodyDef;

class PhysicsComponent : public yam2d::Component, public yam2d::Updatable
{
public:
	PhysicsComponent(yam2d::GameObject* p_owner, b2World* p_world, const b2BodyDef& p_bodyDef);

	void update(float deltaTime);

	yam2d::GameObject* getGameObject() { return static_cast<yam2d::GameObject*>(getOwner()); }
	const yam2d::GameObject* getGameObject() const { return static_cast<const yam2d::GameObject*>(getOwner()); }
private:

	b2Body* m_body;
};