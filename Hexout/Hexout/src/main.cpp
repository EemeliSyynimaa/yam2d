#include "core/app.h"
#include "scenes/gamescene.h"

int main(int argc, char* argv[])
{
	App::run(new GameScene());

	return 0;
}