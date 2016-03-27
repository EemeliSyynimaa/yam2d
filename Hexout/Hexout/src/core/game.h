#pragma once

#include "es_util.h"
#include "core/scenemanager.h"

class Game
{
public:
    Game();

    yam2d::ESContext* getContext() { return m_context; }
    SceneManager* getSceneManager() { return &m_sceneManager; }

	bool init(yam2d::ESContext* context);
	void deinit();
	void update(float deltaTime);
	void render();

private:
    yam2d::ESContext* m_context;
	SceneManager m_sceneManager;
};