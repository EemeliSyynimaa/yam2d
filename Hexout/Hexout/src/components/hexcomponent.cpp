#include "components/hexcomponent.h"

HexComponent::HexComponent(yam2d::GameObject* owner) :
    Component(owner, Component::getDefaultProperties())
{
}

HexComponent::~HexComponent()
{
}

void HexComponent::update(float deltaTime)
{
}

void HexComponent::render()
{
    // TODO hardcode these to somewhere else.
    static const float size = 64.0f;
    static const float positionData[] = 
    {
        0.0f, 0.0f, 0.0f,
        0.5f * size, 0.25f * size, 0.0f,
        0.0f, 0.5f * size, 0.0f,
        -0.5f * size, 0.25f * size, 0.0f,
        -0.5f * size, -0.25f * size, 0.0f,
        0.0f, -0.5f * size, 0.0f,
        0.5f * size, -0.25f * size, 0.0f,
        0.5f * size, 0.25f * size, 0.0f
    };
    
    static const float edgeColor = 0.3f;
    static const float centerColor = 0.8f;
    
    static const float r = 0.5f;
    static const float g = 0.2f;
    static const float b = 0.8f;
    
    static const float colorData[] = 
    {
        centerColor * r, centerColor * g, centerColor * b, 1.0f,
        edgeColor * r, edgeColor * g, edgeColor * b, 1.0f,
        edgeColor * r, edgeColor * g, edgeColor * b, 1.0f,
        edgeColor * r, edgeColor * g, edgeColor * b, 1.0f,
        edgeColor * r, edgeColor * g, edgeColor * b, 1.0f,
        edgeColor * r, edgeColor * g, edgeColor * b, 1.0f,
        edgeColor * r, edgeColor * g, edgeColor * b, 1.0f,
        edgeColor * r, edgeColor * g, edgeColor * b, 1.0f
    };
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &positionData[0]);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, &colorData[0]);
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glScalef(1.0f, 1.0f, 1.0f);;
    glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
    
    glPopMatrix();
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}