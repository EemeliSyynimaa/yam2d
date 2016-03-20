#include "game.h"
#include "gamescene.h"

int main(int argc, char* argv[])
{
	Game::run(new GameScene());

	return 0;
}