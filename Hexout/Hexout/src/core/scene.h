#pragma once

#include "core/game.h"

class Scene
{
public:
    Scene(Game* p_game) : m_game(p_game) {};
	virtual ~Scene() {};
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

protected:
    Game* m_game;
};
