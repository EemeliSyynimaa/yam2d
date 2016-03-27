#include "core/componentfactory.h"
#include "GameObject.h"

ComponentFactory::ComponentFactory() :
    yam2d::DefaultComponentFactory()
{

}

yam2d::Component* ComponentFactory::createNewComponent(const std::string& type, yam2d::Entity* owner, const yam2d::PropertySet& properties)
{
    return yam2d::DefaultComponentFactory::createNewComponent(type, owner, properties);
}

yam2d::Entity* ComponentFactory::createNewEntity(yam2d::ComponentFactory* componentFactory, const std::string& type, yam2d::Entity* parent, const yam2d::PropertySet& properties)
{
    if (type == "Tile")
    {
        yam2d::GameObject* gameobject = new yam2d::GameObject(parent, properties);
        gameobject->addComponent(componentFactory->createNewComponent("Tile", gameobject, properties));
        return gameobject;
    }

    return yam2d::DefaultComponentFactory::createNewEntity(componentFactory, type, parent, properties);
}