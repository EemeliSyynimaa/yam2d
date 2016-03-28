#pragma once

#include "Map.h"
#include "Texture.h"

class ComponentFactory : public yam2d::DefaultComponentFactory
{
public:
    ComponentFactory();

    yam2d::Component* createNewComponent(const std::string& type, yam2d::Entity* owner, const yam2d::PropertySet& properties);
    yam2d::Entity* createNewEntity(yam2d::ComponentFactory* componentFactory, const std::string& type, yam2d::Entity* parent, const yam2d::PropertySet& properties);
private:
    yam2d::Ref<yam2d::Texture> m_ballTexture;
    yam2d::Ref<yam2d::Texture> m_paddleTexture;
};