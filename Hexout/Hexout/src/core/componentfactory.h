#pragma once

#include "Map.h"
#include "Texture.h"
#include "Box2D/Box2D.h"

class ComponentFactory : public yam2d::DefaultComponentFactory
{
public:
    ComponentFactory();

	void setWorld(b2World* p_world) { m_world = p_world; }

    yam2d::Component* createNewComponent(const std::string& type, yam2d::Entity* owner, const yam2d::PropertySet& properties);
    yam2d::Entity* createNewEntity(yam2d::ComponentFactory* componentFactory, const std::string& type, yam2d::Entity* parent, const yam2d::PropertySet& properties);
private:
    yam2d::Ref<yam2d::Texture> m_ballTexture;
    yam2d::Ref<yam2d::Texture> m_paddleTexture;
	yam2d::Ref<b2World> m_world;
};