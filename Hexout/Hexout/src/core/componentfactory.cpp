#include "core/componentfactory.h"
#include "core/b2util.h"
#include "components/paddlecomponent.h"
#include "components/physicscomponent.h"

#include "GameObject.h"
#include "SpriteComponent.h"

#include <iostream>

ComponentFactory::ComponentFactory() :
    yam2d::DefaultComponentFactory()
{
    m_ballTexture = new yam2d::Texture("assets/textures/ball.png");
    m_paddleTexture = new yam2d::Texture("assets/textures/paddle.png");

	m_ballTexture->setTransparentColor(255, 0, 255);
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

		//b2BodyDef b;
		//b.type = b2_staticBody;
		//b.angle = 0;
		//b.position = worldToBox2D(p_gameObject->getPosition());

		//b2Body* p_body = m_world->CreateBody(&b);

		//b2PolygonShape boxShape;
		//boxShape.SetAsBox(worldToBox2D(1), worldToBox2D(1));

		//b2FixtureDef boxFixtureDef;
		//boxFixtureDef.shape = &boxShape;
		//boxFixtureDef.density = 1;
		//p_body->CreateFixture(&boxFixtureDef);

		//p_gameObject->addComponent(new PhysicsComponent(p_gameObject, m_world, p_body));

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

		b2BodyDef b;
		b.type = b2_dynamicBody;
		b.position.Set(0, 0);
		b.angle = 0;

		b2Body* p_body = m_world->CreateBody(&b);

		b2PolygonShape boxShape;

		boxShape.SetAsBox(worldToBox2D(64.0f), worldToBox2D(8.0f)); 

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		p_body->CreateFixture(&boxFixtureDef);

        p_gameObject->addComponent(new yam2d::SpriteComponent(p_gameObject, m_paddleTexture));
        p_gameObject->addComponent(new PaddleComponent(p_gameObject));
		p_gameObject->addComponent(new PhysicsComponent(p_gameObject, m_world, p_body));

        return p_gameObject;
    }

    return yam2d::DefaultComponentFactory::createNewEntity(p_componentFactory, type, p_parent, properties);
}