#pragma once

#include "scene.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void init();
	void deinit();
	void update(float deltaTime);
	void render();

private:
};
