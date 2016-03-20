#pragma once

#include "es_util.h"
#include "scenemanager.h"

class Game
{
public:
	static void run(Scene* scene);

private:
	static bool init(yam2d::ESContext* context);
	static void deinit(yam2d::ESContext* context);
	static void update(yam2d::ESContext* context, float deltaTime);
	static void render(yam2d::ESContext* context);

	static yam2d::ESContext context;
	static SceneManager sceneManager;
};