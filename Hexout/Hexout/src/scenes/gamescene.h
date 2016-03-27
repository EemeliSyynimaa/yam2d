#pragma once

#include "core/scene.h"
#include "core/componentfactory.h"

#include "Sprite.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Map.h"

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void update(float deltaTime);
    void render();

private:
    yam2d::TmxMap* m_map;
    yam2d::ComponentFactory* m_componentFactory;

    float m_zoom = 1.0f;
};