#include "scenes/gamescene.h"
#include "scenes/menuscene.h"

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

#include <algorithm>
#include <iostream>

GameScene::GameScene(Game* p_game) : 
    Scene(p_game),
    m_map(new yam2d::TmxMap()),
    m_world(new b2World(b2Vec2(0.0f, 0.0f))),
    m_componentFactory(new ComponentFactory(m_world, m_map)),
    m_collisionHandler(new CollisionHandler(m_map)),
    m_score(0),
    m_lives(5),
    m_tiles(0),
    m_zoom(0.0f),
    m_step(1.0f / 20.0f),
    m_gameOver(false)
{
    m_world->SetContactListener(m_collisionHandler);

    m_map->loadMapFile("assets/levels/testi.tmx", m_componentFactory);
    m_map->getCamera()->setPosition(m_map->findGameObjectByName("origin")->getPosition());

    m_background = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Background", nullptr, yam2d::PropertySet()));
    m_paddle = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Paddle", nullptr, yam2d::PropertySet()));
    m_ball = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Ball", nullptr, yam2d::PropertySet()));
	m_scoreLabel = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Label", nullptr, yam2d::PropertySet()));
    m_livesLabel = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Label", nullptr, yam2d::PropertySet()));
    m_gameOverLabel = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Label", nullptr, yam2d::PropertySet()));
    m_backToMenuLabel = static_cast<yam2d::GameObject*>(m_componentFactory->createNewEntity(m_componentFactory, "Label", nullptr, yam2d::PropertySet()));

    // Update screen size to ball and paddle. Their movement depend on the size of the screen.
    m_paddle->getComponent<PaddleComponent>()->setScreenSize(m_game->getContext()->width, m_game->getContext()->height);
    m_ball->getComponent<BallComponent>()->setScreenSize(m_game->getContext()->width, m_game->getContext()->height);

	m_scoreLabel->getComponent<yam2d::TextComponent>()->getText()->setText("Score: " + std::to_string(m_score));
	m_scoreLabel->getComponent<yam2d::TextComponent>()->getText()->setColor(255.0f, 255.0f, 255.0f, 1.0f);
    m_scoreLabel->setPosition(m_map->findGameObjectByName("origin")->getPosition().x, -5.0f);

    m_livesLabel->getComponent<yam2d::TextComponent>()->getText()->setText("Lives: " + std::to_string(m_lives));
    m_livesLabel->getComponent<yam2d::TextComponent>()->getText()->setColor(255.0f, 0.0f, 0.0f, 1.0f);
    m_livesLabel->setPosition(m_map->findGameObjectByName("origin")->getPosition().x, 16.0f);

    m_gameOverLabel->getComponent<yam2d::TextComponent>()->getText()->setText("");
    m_gameOverLabel->getComponent<yam2d::TextComponent>()->getText()->setColor(255.0f, 0.0f, 255.0f, 1.0f);
    m_gameOverLabel->setPosition(m_map->findGameObjectByName("origin")->getPosition().x, -1.0f);

    m_backToMenuLabel->getComponent<yam2d::TextComponent>()->getText()->setText("");
    m_backToMenuLabel->getComponent<yam2d::TextComponent>()->getText()->setColor(255.0f, 255.0f, 0.0f, 1.0f);
    m_backToMenuLabel->setPosition(m_map->findGameObjectByName("origin")->getPosition().x, 12.0f);

    m_tiles = getNumberOfGameObjectsOfType("HexTile");

    std::cout << m_tiles << std::endl;
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

            m_tiles -= deadObjects;

            // Checks if the tiles are destroyed.
            if (m_tiles == 0)
            {
                // We add extra points for remaining lives.
                updateScore(m_lives * 500);
                m_gameOverLabel->getComponent<yam2d::TextComponent>()->getText()->setText("YOU WIN");
                m_backToMenuLabel->getComponent<yam2d::TextComponent>()->getText()->setText("Press left mouse button");
                m_gameOver = true;
            }
        }

        // Check if the ball is dead.
        if (m_ball->getComponent<BallComponent>()->isDead())
        {
            // Ball is dead and we have run out of lives. Game over and player lost.
            if (m_lives == 0)
            {
                m_gameOverLabel->getComponent<yam2d::TextComponent>()->getText()->setText("YOU LOSE");
                m_backToMenuLabel->getComponent<yam2d::TextComponent>()->getText()->setText("Press left mouse button");
                m_gameOver = true;
            }
            // Ball is dead but we still have some lives left. Decrease lives and revive the ball.
            else
            {
                updateLives(-1);
                m_ball->getComponent<BallComponent>()->revive();
            }
        }
    }

    if (m_gameOver && yam2d::isMouseButtonPressed(yam2d::MOUSE_LEFT))
    {
        m_game->getSceneManager()->change(new MenuScene(m_game));
    }
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

size_t GameScene::getNumberOfGameObjectsOfType(const std::string& type)
{
    return std::count_if(std::begin(m_map->getLayer("GameObjects")->getGameObjects()), std::end(m_map->getLayer("GameObjects")->getGameObjects()), [&type](yam2d::GameObject* gameObject)
    {
        return (gameObject->getType() == type);
    });
}