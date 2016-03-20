#include "game.h"

yam2d::ESContext Game::context;
SceneManager Game::sceneManager;

void Game::run(Scene* scene)
{
	if (!scene) return;

	sceneManager.change(scene);

	yam2d::esInitContext(&context);
	yam2d::esCreateWindow(&context, "Hexout", 1280, 720, yam2d::ES_WINDOW_DEFAULT);

	yam2d::esRegisterInitFunc(&context, Game::init);
	yam2d::esRegisterDeinitFunc(&context, Game::deinit);
	yam2d::esRegisterUpdateFunc(&context, Game::update);
	yam2d::esRegisterDrawFunc(&context, Game::render);

	glViewport(0, 0, context.width, context.height);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	yam2d::esMainLoop(&context);
}

bool Game::init(yam2d::ESContext* context)
{
	sceneManager.init();	

	return true;
}

void Game::deinit(yam2d::ESContext* context)
{
	sceneManager.deinit();
}

void Game::update(yam2d::ESContext* context, float deltaTime)
{
	sceneManager.update(deltaTime);
}

void Game::render(yam2d::ESContext* context)
{
	sceneManager.render();
	glClear(GL_COLOR_BUFFER_BIT);
}

