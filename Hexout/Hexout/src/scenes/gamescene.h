#pragma once

#include "core/scene.h"
#include "core/componentfactory.h"
#include "core/collisionhandler.h"

class b2World;

class GameScene : public Scene
{
public:
    GameScene(Game* p_game);
    ~GameScene();

    void update(float deltaTime);
    void render();

private:
    void updateScore(int amount);
    void updateLives(int amount);

    yam2d::Ref<yam2d::TmxMap> m_map;
    yam2d::Ref<b2World> m_world;
    yam2d::Ref<ComponentFactory> m_componentFactory;
    yam2d::Ref<CollisionHandler> m_collisionHandler;

    yam2d::Ref<yam2d::GameObject> m_ball;
    yam2d::Ref<yam2d::GameObject> m_paddle;
	yam2d::Ref<yam2d::GameObject> m_scoreLabel;
    yam2d::Ref<yam2d::GameObject> m_livesLabel;
    yam2d::Ref<yam2d::GameObject> m_gameOverLabel;

	size_t m_score;
    size_t m_lives;

    float m_zoom;
    float m_step;

    bool m_gameOver;
};