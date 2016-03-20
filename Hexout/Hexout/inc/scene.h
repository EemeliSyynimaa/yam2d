#pragma once

class Scene
{
public:
	virtual ~Scene() {};
	virtual void init() = 0;
	virtual void deinit() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
private:
};
