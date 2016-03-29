#include "scenes/gamescene.h"
#include "es_util.h"
#include "Camera.h"
#include "Layer.h"

GameScene::GameScene(Game* p_game) : 
    Scene(p_game)
{
    m_map = new yam2d::TmxMap();
    m_componentFactory = new ComponentFactory();

    m_map->loadMapFile("assets/levels/testi.tmx", m_componentFactory);
    m_map->getCamera()->setPosition(yam2d::vec2(m_map->getWidth() / 2.0f - 0.5f, m_map->getHeight() / 2.0f - 0.5f));

    m_ball = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Ball", nullptr, yam2d::PropertySet()));
    m_paddle = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Paddle", nullptr, yam2d::PropertySet()));

    m_map->getLayer("GameObjects")->addGameObject(m_ball);
    m_map->getLayer("GameObjects")->addGameObject(m_paddle);
}

GameScene::~GameScene()
{
}

void GameScene::update(float deltaTime)
{
    m_map->update(deltaTime);
}

void GameScene::render()
{
    m_map->getCamera()->setScreenSize(m_game->getContext()->width, m_game->getContext()->height);
    m_map->render();
}