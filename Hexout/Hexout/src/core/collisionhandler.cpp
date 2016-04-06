#include "core/collisionhandler.h"

CollisionHandler::CollisionHandler(yam2d::TmxMap* p_map) :
    m_map(p_map)
{
}

void CollisionHandler::BeginContact(b2Contact* contact)
{
	yam2d::GameObject* a = static_cast<yam2d::GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
	yam2d::GameObject* b = static_cast<yam2d::GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

	handleCollision(a, b);
	handleCollision(b, a);
}

void CollisionHandler::EndContact(b2Contact* contact)
{
}

void CollisionHandler::handleCollision(yam2d::GameObject* a, yam2d::GameObject* b)
{
    if (a->getType() == "HexTile")
    {
        deadObjects.push_back(a);
    }
}

size_t CollisionHandler::deleteDeadObjects()
{
	size_t size = deadObjects.size();
    for (auto object : deadObjects)
    {
        m_map->deleteGameObject(object);
    }

    deadObjects.clear();

	return size;
}