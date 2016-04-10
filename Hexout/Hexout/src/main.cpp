#include "es_util.h"
#include "core/game.h"
#include "scenes/menuscene.h"

Game* p_game;

bool init(yam2d::ESContext* p_context)
{
    p_game = new Game();
    p_game->init(p_context);
    p_game->getSceneManager()->change(new MenuScene(p_game));

    return true;
}

void deinit(yam2d::ESContext* p_context)
{
    p_game->deinit();

    delete p_game;
}

void update(yam2d::ESContext* p_context, float deltaTime)
{
    p_game->update(deltaTime);
}

void render(yam2d::ESContext* p_context)
{
    p_game->render();
}

int main(int argc, char* argv[])
{
    yam2d::ESContext context;
    yam2d::esInitContext(&context);
    yam2d::esCreateWindow(&context, "Hexout", 750, 750, yam2d::ES_WINDOW_DEFAULT);

    yam2d::esRegisterInitFunc(&context, init);
    yam2d::esRegisterDeinitFunc(&context, deinit);
    yam2d::esRegisterUpdateFunc(&context, update);
    yam2d::esRegisterDrawFunc(&context, render);

    yam2d::esMainLoop(&context);

    return 0;
}