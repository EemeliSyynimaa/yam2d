#include "core/scenemanager.h"
#include "core/scene.h"

SceneManager::SceneManager(Game* p_game) :
    m_game(p_game)
{
}

SceneManager::~SceneManager()
{
    for (Scene* p_scene : m_scenes)
	{
        delete p_scene;
	}

    m_scenes.clear();
}

void SceneManager::update(float deltaTime)
{
    if (!m_scenes.empty()) m_scenes.back()->update(deltaTime);
}

void SceneManager::render()
{
    for (Scene* p_scene : m_scenes)
	{
		p_scene->render();
	}
}

void SceneManager::push(Scene* p_scene)
{
    if (p_scene)
	{
        p_scene->setGame(m_game);
        m_scenes.push_back(p_scene);
	}
}

void SceneManager::change(Scene* p_scene)
{
    if (p_scene)
    {
        clear();

        p_scene->setGame(m_game);
        m_scenes.push_back(p_scene);
    }
}

void SceneManager::pop()
{
	if (!m_scenes.empty())
	{
        delete m_scenes.back();
        m_scenes.pop_back();
	}
}

void SceneManager::clear()
{
    for (Scene* p_scene : m_scenes)
	{
        delete p_scene;
	}

    m_scenes.clear();
}