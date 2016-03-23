#include "scenemanager.h"
#include "scene.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	for (Scene* scene : scenes)
	{
		delete scene;
	}

	scenes.clear();
}

void SceneManager::init()
{
	if(!scenes.empty()) scenes.back()->init();
}

void SceneManager::deinit()
{
	if(!scenes.empty()) scenes.back()->deinit();
}

void SceneManager::update(float deltaTime)
{
	if (!scenes.empty()) scenes.back()->update(deltaTime);
}

void SceneManager::render()
{
	for (Scene* scene : scenes)
	{
		scene->render();
	}
}

void SceneManager::push(Scene* scene)
{
	if (scene)
	{
		scenes.push_back(scene);
	}
}

void SceneManager::change(Scene* scene)
{
	clear();

	scenes.push_back(scene);
}

void SceneManager::pop()
{
	if (!scenes.empty())
	{
		delete scenes.back();
		scenes.pop_back();
	}
}

void SceneManager::clear()
{
	for (Scene* scene : scenes)
	{
		delete scene;
	}

	scenes.clear();
}