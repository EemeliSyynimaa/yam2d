#include "core/componentfactory.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "components/paddlecomponent.h"

ComponentFactory::ComponentFactory() :
    yam2d::DefaultComponentFactory()
{
    m_ballTexture = new yam2d::Texture("assets/textures/ball.png");
    m_ballTexture->setTransparentColor(255, 0, 255);

    m_paddleTexture = new yam2d::Texture("assets/textures/paddle.png");
}

yam2d::Component* ComponentFactory::createNewComponent(const std::string& type, yam2d::Entity* p_owner, const yam2d::PropertySet& properties)
{
    return yam2d::DefaultComponentFactory::createNewComponent(type, p_owner, properties);
}

yam2d::Entity* ComponentFactory::createNewEntity(yam2d::ComponentFactory* p_componentFactory, const std::string& type, yam2d::Entity* p_parent, const yam2d::PropertySet& properties)
{
    if (type == "HexTile")
    {
        yam2d::GameObject* p_gameObject = new yam2d::GameObject(p_parent, properties);

        p_gameObject->addComponent(p_componentFactory->createNewComponent("Tile", p_gameObject, properties));

        return p_gameObject;
    }
    else if (type == "Ball")
    {
        yam2d::GameObject* p_gameObject = new yam2d::GameObject(nullptr, 0);

        p_gameObject->addComponent(new yam2d::SpriteComponent(p_gameObject, m_ballTexture));

        return p_gameObject;
    }
    else if (type == "Paddle")
    {
        yam2d::GameObject* p_gameObject = new yam2d::GameObject(nullptr, 0);

        p_gameObject->addComponent(new yam2d::SpriteComponent(p_gameObject, m_paddleTexture));
        p_gameObject->addComponent(new PaddleComponent(p_gameObject));

        return p_gameObject;
    }

    return yam2d::DefaultComponentFactory::createNewEntity(p_componentFactory, type, p_parent, properties);
}