#include "scenes/gamescene.h"
#include "es_util.h"
#include "Camera.h"

GameScene::GameScene()
{

    m_map = new yam2d::TmxMap();
    m_componentFactory = new ComponentFactory();

    m_map->loadMapFile("assets/levels/testi.tmx", m_componentFactory);
    m_map->getCamera()->setPosition(yam2d::vec2(m_map->getWidth() / 2.0f - 0.5f, m_map->getHeight() / 2.0f - 0.5f));
}

GameScene::~GameScene()
{
    delete m_map;
    delete m_componentFactory;
}

void GameScene::update(float deltaTime)
{
}

void GameScene::render()
{
    m_map->getCamera()->setScreenSize(m_game->getContext()->width, m_game->getContext()->height);
    m_map->render();
}