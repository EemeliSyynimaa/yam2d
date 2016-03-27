#pragma once

#include "GameObject.h"

class HexComponent : public yam2d::Component, public yam2d::Updatable
{
public:
    HexComponent(yam2d::Entity* owner, const yam2d::PropertySet& properties);
    ~HexComponent();
    
    void update(float deltaTime);
    void render();
private:
};