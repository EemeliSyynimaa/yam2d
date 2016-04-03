#include "scenes/gamescene.h"
#include "es_util.h"
#include "Camera.h"
#include "Layer.h"
#include "Input.h"

#include "components/physicscomponent.h"
#include "Box2D/Box2D.h"

#include <iostream>

GameScene::GameScene(Game* p_game) : 
    Scene(p_game)
{
	m_world = new b2World(b2Vec2(0.0f, 0.0f));
    m_map = new yam2d::TmxMap();

    m_componentFactory = new ComponentFactory();
	m_componentFactory->setWorld(m_world);
    m_componentFactory->setMap(m_map);

    m_collisionHandler = new CollisionHandler();
    m_collisionHandler->setMap(m_map);
    m_world->SetContactListener(m_collisionHandler);

    m_map->loadMapFile("assets/levels/testi.tmx", m_componentFactory);

    yam2d::vec2 origin = m_map->findGameObjectByName("origin")->getPosition();

    m_map->getCamera()->setPosition(origin);

    m_ball = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Ball", nullptr, yam2d::PropertySet()));
    m_paddle = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Paddle", nullptr, yam2d::PropertySet()));
}

GameScene::~GameScene()
{
}

void GameScene::update(float deltaTime)
{
	m_world->Step(1 / 20.0f, 8, 3);
    m_map->update(deltaTime);

    m_collisionHandler->deleteDeadObjects();

    //b2Vec2 direction = m_ball->getComponent<PhysicsComponent>()->getBody()->GetLinearVelocity();
    //direction.Normalize();

    //static float speed = 128.0f;
    //b2Vec2 velocity = speed * deltaTime * direction;

    //m_ball->getComponent<PhysicsComponent>()->getBody()->SetLinearVelocity(velocity);
}

void GameScene::render()
{
    m_map->getCamera()->setScreenSize(m_game->getContext()->width, m_game->getContext()->height);
    m_map->render();
}