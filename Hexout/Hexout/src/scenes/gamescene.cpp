#include "scenes/gamescene.h"
#include "es_util.h"
#include "Camera.h"
#include "Layer.h"
#include "Input.h"
#include "TextComponent.h"

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
	m_scoreLabel = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Label", nullptr, yam2d::PropertySet()));

	m_scoreLabel->getComponent<yam2d::TextComponent>()->getText()->setText("Score: 0");
	m_scoreLabel->getComponent<yam2d::TextComponent>()->getText()->setColor(255.0f, 255.0f, 255.0f, 1.0f);
	m_scoreLabel->setPosition(origin.x, -5.0f);
}

GameScene::~GameScene()
{
}

void GameScene::update(float deltaTime)
{
	m_world->Step(m_step, 8, 3);

	int deadObjects = m_collisionHandler->deleteDeadObjects();
    
	if (deadObjects > 0)
	{
		m_speed += deadObjects * 2.0f;
		m_score += deadObjects * 100;
		m_scoreLabel->getComponent<yam2d::TextComponent>()->getText()->setText("Score: " +  std::to_string(m_score));
	}

    b2Vec2 direction = m_ball->getComponent<PhysicsComponent>()->getBody()->GetLinearVelocity();
    direction.Normalize();

    b2Vec2 velocity = m_speed * deltaTime * direction;

    m_ball->getComponent<PhysicsComponent>()->getBody()->SetLinearVelocity(velocity);

	m_map->update(deltaTime);
}

void GameScene::render()
{
    m_map->getCamera()->setScreenSize(m_game->getContext()->width, m_game->getContext()->height);
    m_map->render();
}