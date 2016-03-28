#pragma once

#include "GameObject.h"

class HexComponent : public yam2d::Component, public yam2d::Updatable
{
public:
    HexComponent(yam2d::GameObject* owner);
    ~HexComponent();
    
    void update(float deltaTime);
    void render();
private:
};