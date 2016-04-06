#include "core/game.h"
#include "scenes/gamescene.h"

#include "Input.h"

Game::Game() :
    m_context(nullptr),
    m_sceneManager(this)
{
}

bool Game::init(yam2d::ESContext* p_context)
{
    m_context = p_context;

    glViewport(0, 0, m_context->width, m_context->height);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrthof(-0.5f * m_context->width, 0.5f * m_context->width, -0.5f * m_context->height, 0.5f * m_context->height, -1.0, 1.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Game::deinit()
{
}

void Game::update(float deltaTime)
{
    m_sceneManager.update(deltaTime);

    if (yam2d::getKeyState(yam2d::KEY_ESCAPE))
    {
        yam2d::esQuitApp(m_context);
    }
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_sceneManager.render();
}

