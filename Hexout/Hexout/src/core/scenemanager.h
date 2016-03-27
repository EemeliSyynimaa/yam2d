#pragma once

#include <vector>

class Scene;
class Game;

class SceneManager
{
public:
	SceneManager(Game* p_game);
	~SceneManager();

	void update(float deltaTime);
	void render();

    void push(Scene* p_scene);
	void pop();
    void change(Scene* p_scene);
	
private:
	void clear();

	std::vector<Scene*> m_scenes;
    Game* m_game;
};