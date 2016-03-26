#include "core/app.h"

yam2d::ESContext App::context;
SceneManager App::sceneManager;

void App::run(Scene* scene)
{
	if (!scene) return;

	sceneManager.change(scene);

	yam2d::esInitContext(&context);
	yam2d::esCreateWindow(&context, "Hexout", 1280, 720, yam2d::ES_WINDOW_DEFAULT);

	yam2d::esRegisterInitFunc(&context, App::init);
	yam2d::esRegisterDeinitFunc(&context, App::deinit);
	yam2d::esRegisterUpdateFunc(&context, App::update);
	yam2d::esRegisterDrawFunc(&context, App::render);

	glViewport(0, 0, context.width, context.height);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	yam2d::esMainLoop(&context);
}

bool App::init(yam2d::ESContext* context)
{
	return true;
}

void App::deinit(yam2d::ESContext* context)
{
}

void App::update(yam2d::ESContext* context, float deltaTime)
{
	sceneManager.update(deltaTime);
}

void App::render(yam2d::ESContext* context)
{
	sceneManager.render();
	glClear(GL_COLOR_BUFFER_BIT);
}

