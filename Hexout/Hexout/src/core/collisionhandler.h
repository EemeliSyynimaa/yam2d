#pragma once

#include "Box2D/Box2D.h"
#include "Object.h"
#include "GameObject.h"
#include "Map.h"

#include <vector>

class CollisionHandler : public b2ContactListener, public yam2d::Object
{
public:
    CollisionHandler(yam2d::TmxMap* p_map);
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    size_t deleteDeadObjects();
private:
    void handleCollision(yam2d::GameObject* a, yam2d::GameObject* b);

    std::vector<yam2d::GameObject*> deadObjects;
    yam2d::Ref<yam2d::TmxMap> m_map;
};