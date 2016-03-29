#pragma once

#include "core/scene.h"
#include "core/componentfactory.h"

#include "Box2D/Box2D.h"

class GameScene : public Scene
{
public:
    GameScene(Game* p_game);
    ~GameScene();

    void update(float deltaTime);
    void render();

private:
    yam2d::Ref<yam2d::TmxMap> m_map;
    yam2d::Ref<ComponentFactory> m_componentFactory;
    yam2d::Ref<yam2d::GameObject> m_ball;
    yam2d::Ref<yam2d::GameObject> m_paddle;

    float m_zoom = 1.0f;

};