#pragma once

#include "core/scene.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void update(float deltaTime);
	void render();

private:
};
