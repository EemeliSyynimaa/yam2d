#pragma once

#include "core/game.h"

class Scene
{
public:
	virtual ~Scene() {};
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

    void setGame(Game* game) { m_game = game; }
protected:
    Game* m_game;
};
