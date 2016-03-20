#pragma once

#include <vector>

class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void init();
	void deinit();
	void update(float deltaTime);
	void render();

	void push(Scene* scene);
	void pop();
	void change(Scene* scene);
	
private:
	void clear();

	std::vector<Scene*> scenes;
};