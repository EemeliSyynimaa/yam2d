#include "es_util.h"

bool init(yam2d::ESContext* esContext)
{
	return true;
}

void deinit(yam2d::ESContext* esContext)
{

}

void draw(yam2d::ESContext* esContext)
{
	glViewport(0, 0, esContext->width, esContext->height);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
}

void update(yam2d::ESContext* esContext, float deltaTime)
{

}

int main(int argc, char* argv[])
{
	yam2d::ESContext esContext;

	yam2d::esInitContext(&esContext);
	yam2d::esCreateWindow(&esContext, "Hello Yam2D", 1280, 720, yam2d::ES_WINDOW_DEFAULT);

	if (!init(&esContext))
	{
		return 0;
	}

	yam2d::esRegisterInitFunc(&esContext, init);
	yam2d::esRegisterDrawFunc(&esContext, draw);
	yam2d::esRegisterUpdateFunc(&esContext, update);
	yam2d::esRegisterDeinitFunc(&esContext, deinit);

	yam2d::esMainLoop(&esContext);

	return 0;
}