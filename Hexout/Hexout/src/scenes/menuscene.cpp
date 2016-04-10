#include "scenes/menuscene.h"
#include "scenes/gamescene.h"

#include "Layer.h"
#include "Texture.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "Input.h"

MenuScene::MenuScene(Game* p_game) : 
    Scene(p_game),
    m_map(new yam2d::Map(64.0f, 64.0f)),
    m_zoom(1.0f),
    m_selected(0)
{
    m_map->addLayer(yam2d::Map::BACKGROUND0, new yam2d::Layer(m_map, "Background", 1.0f, true, false));
    m_map->addLayer(yam2d::Map::GUILAYER0, new yam2d::Layer(m_map, "GUI", 1.0f, true, false));

    m_background = createSprite("assets/textures/background.png", 760.0f, 760.0f);
    m_startgame = createSprite("assets/textures/startgame.png", 200.0f, 65.0f);
    m_quitgame = createSprite("assets/textures/quitgame.png", 200.0f, 65.0f);

    m_startgame->setPosition(yam2d::vec2(3.7f, 3.0f));
    m_quitgame->setPosition(yam2d::vec2(3.7f, 4.5f));

    m_map->getLayer("Background")->addGameObject(m_background);
    m_map->getLayer("GUI")->addGameObject(m_startgame);
    m_map->getLayer("GUI")->addGameObject(m_quitgame);
}

MenuScene::~MenuScene()
{

}

void MenuScene::update(float deltaTime)
{
    if (yam2d::isKeyPressed(yam2d::KEY_UP))
    {
        if (m_selected == 0) 
            m_selected = 1;
        else 
            m_selected = 0;
    }
    if (yam2d::isKeyPressed(yam2d::KEY_DOWN))
    {
        if (m_selected == 1) 
            m_selected = 0;
        else 
            m_selected = 1;
    }
    if (yam2d::isKeyPressed(yam2d::KEY_SPACE))
    {
        if (m_selected == 0)
            m_game->getSceneManager()->change(new GameScene(m_game));
        else
            m_game->getContext()->quitFlag = true;
    }
}

void MenuScene::render()
{
    if (m_selected == 0)
    {
        m_startgame->getComponent<yam2d::SpriteComponent>()->setColor(255.0f, 255.0f, 0.0f, 1.0f);
        m_quitgame->getComponent<yam2d::SpriteComponent>()->setColor(255.0f, 255.0f, 255.0f, 1.0f);
    }
    else
    {
        m_startgame->getComponent<yam2d::SpriteComponent>()->setColor(255.0f, 255.0f, 255.0f, 1.0f);
        m_quitgame->getComponent<yam2d::SpriteComponent>()->setColor(255.0f, 255.0f, 0.0f, 1.0f);
    }

    m_map->getCamera()->setScreenSize(m_game->getContext()->width, m_game->getContext()->height);
    m_map->render();
}

yam2d::GameObject* MenuScene::createSprite(const std::string& path, float width, float height)
{
    yam2d::Texture* p_texture = new yam2d::Texture(path.c_str());

    yam2d::GameObject* p_gameObject = new yam2d::GameObject(0, 0);
    p_gameObject->setSize(width, height);
    p_gameObject->addComponent(new yam2d::SpriteComponent(p_gameObject, p_texture));
    p_gameObject->getComponent<yam2d::SpriteComponent>()->setRenderingEnabled(true);

    return p_gameObject;
}