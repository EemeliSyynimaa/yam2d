#include "components/paddlecomponent.h"
#include "Input.h"
#include "vec2.h"

PaddleComponent::PaddleComponent(yam2d::GameObject* p_owner) :
    Component(p_owner, Component::getDefaultProperties()), m_angle(0.0f), m_position(0.0f, 0.0f), m_moved(true), m_radius(8.0f)
{
}

void PaddleComponent::update(float deltaTime)
{
}