#pragma once

class Scene
{
public:
	virtual ~Scene() {};
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
private:
};
