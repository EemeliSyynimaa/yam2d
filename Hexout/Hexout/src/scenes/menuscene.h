#pragma once

#include "core/scene.h"
#include "Map.h"

class MenuScene : public Scene
{
public:
    MenuScene(Game* p_game);
    ~MenuScene();

    void update(float deltaTime);
    void render();

private:

    yam2d::GameObject* createSprite(const std::string& path, float width, float height);

    yam2d::Ref<yam2d::Map> m_map;
    yam2d::Ref<yam2d::GameObject> m_background;
    yam2d::Ref<yam2d::GameObject> m_startgame;
    yam2d::Ref<yam2d::GameObject> m_quitgame;

    float m_zoom;
    size_t m_selected;
};