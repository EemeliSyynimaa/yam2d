#include "core/collisionhandler.h"

void CollisionHandler::BeginContact(b2Contact* contact)
{
}

void CollisionHandler::EndContact(b2Contact* contact)
{
    yam2d::GameObject* a = static_cast<yam2d::GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
    yam2d::GameObject* b = static_cast<yam2d::GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());

    handleCollision(a, b);
    handleCollision(b, a);
}

void CollisionHandler::handleCollision(yam2d::GameObject* a, yam2d::GameObject* b)
{
    if (a->getType() == "HexTile")
    {
        deadObjects.push_back(a);
    }
}

void CollisionHandler::deleteDeadObjects()
{
    for (auto object : deadObjects)
    {
        m_map->deleteGameObject(object);
    }

    deadObjects.clear();
}