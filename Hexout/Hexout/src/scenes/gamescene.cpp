#include "scenes/gamescene.h"

#include "es_util.h"
#include "Camera.h"
#include "Layer.h"
#include "Input.h"
#include "TextComponent.h"
#include "SpriteComponent.h"

#include "components/physicscomponent.h"
#include "components/paddlecomponent.h"
#include "components/ballcomponent.h"
#include "Box2D/Box2D.h"

#include <iostream>

GameScene::GameScene(Game* p_game) : 
    Scene(p_game),
    m_map(new yam2d::TmxMap()),
    m_world(new b2World(b2Vec2(0.0f, 0.0f))),
    m_componentFactory(new ComponentFactory(m_world, m_map)),
    m_collisionHandler(new CollisionHandler(m_map)),
    m_score(0),
    m_lives(3),
    m_zoom(0.0f),
    m_step(1.0f / 20.0f),
    m_gameOver(false)
{
    m_world->SetContactListener(m_collisionHandler);

    m_map->loadMapFile("assets/levels/testi.tmx", m_componentFactory);
    m_map->getCamera()->setPosition(m_map->findGameObjectByName("origin")->getPosition());

    m_paddle = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Paddle", nullptr, yam2d::PropertySet()));
    m_ball = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Ball", nullptr, yam2d::PropertySet()));
	m_scoreLabel = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Label", nullptr, yam2d::PropertySet()));
    m_livesLabel = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Label", nullptr, yam2d::PropertySet()));
    m_gameOverLabel = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Label", nullptr, yam2d::PropertySet()));

	m_scoreLabel->getComponent<yam2d::TextComponent>()->getText()->setText("Score: " + std::to_string(m_score));
	m_scoreLabel->getComponent<yam2d::TextComponent>()->getText()->setColor(255.0f, 255.0f, 255.0f, 1.0f);
    m_scoreLabel->setPosition(m_map->findGameObjectByName("origin")->getPosition().x, -5.0f);

    m_livesLabel->getComponent<yam2d::TextComponent>()->getText()->setText("Lives: " + std::to_string(m_lives));
    m_livesLabel->getComponent<yam2d::TextComponent>()->getText()->setColor(255.0f, 0.0f, 0.0f, 1.0f);
    m_livesLabel->setPosition(m_map->findGameObjectByName("origin")->getPosition().x, 15.0f);

    m_gameOverLabel->getComponent<yam2d::TextComponent>()->getText()->setText("");
    m_gameOverLabel->getComponent<yam2d::TextComponent>()->getText()->setColor(255.0f, 0.0f, 255.0f, 1.0f);
    m_gameOverLabel->setPosition(m_map->findGameObjectByName("origin")->getPosition().x, -1.0f);
}

GameScene::~GameScene()
{
}

void GameScene::update(float deltaTime)
{
    // Update physics and map.
    m_world->Step(m_step, 8, 3);
    m_map->update(deltaTime);

    // We update only if the game is not over.
    if (!m_gameOver)
    {
        // Deletes the dead objects (tiles) in the map. Returns the sum of deleted objects so we can update
        // the score and the speed of the ball.
        int deadObjects = m_collisionHandler->deleteDeadObjects();

        if (deadObjects > 0)
        {
            // The speed of the ball increases when a tile is destroyed.
            m_ball->getComponent<BallComponent>()->speedUp(deadObjects * 1.5f);

            // Player gets score based on destroyed tiles.
            updateScore(deadObjects * 100);
        }

        // Check if the ball is dead.
        if (m_ball->getComponent<BallComponent>()->isDead())
        {
            // Ball is dead and we have run out of lives. Game over and player lost.
            if (m_lives == 0)
            {
                m_gameOverLabel->getComponent<yam2d::TextComponent>()->getText()->setText("YOU LOSE");
                m_gameOver = true;
            }
            // Ball is dead but we still have some lives left. Decrease lives and revive the ball.
            else
            {
                updateLives(-1);
                m_ball->getComponent<BallComponent>()->revive();
            }
        }

        // Checks if the tiles are destroyed. 5 is the magic number of other objects (m_ball, m_paddle etc.) so if the
        // amount of gameobjects go below that all the tiles must have been destroyed.
        if (m_map->getLayer("GameObjects")->getGameObjects().size() <= 5)
        {
            // We add extra points for remaining lives.
            updateScore(m_lives * 500.0f);
            m_gameOverLabel->getComponent<yam2d::TextComponent>()->getText()->setText("YOU WIN");
            m_gameOver = true;
        }
    }

    // Update screen size to ball and paddle. Their movement depend on the size of the screen.
    m_paddle->getComponent<PaddleComponent>()->setScreenSize(m_game->getContext()->width, m_game->getContext()->height);
    m_ball->getComponent<BallComponent>()->setScreenSize(m_game->getContext()->width, m_game->getContext()->height);
}

void GameScene::render()
{
    m_map->getCamera()->setScreenSize(m_game->getContext()->width, m_game->getContext()->height);
    m_map->render();
}

void GameScene::updateScore(int amount)
{
    m_score += amount;
    m_scoreLabel->getComponent<yam2d::TextComponent>()->getText()->setText("Score: " + std::to_string(m_score));
}

void GameScene::updateLives(int amount)
{
    m_lives += amount;
    m_livesLabel->getComponent<yam2d::TextComponent>()->getText()->setText("Lives: " + std::to_string(m_lives));
}