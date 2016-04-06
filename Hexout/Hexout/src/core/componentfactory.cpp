#include "core/componentfactory.h"
#include "components/paddlecomponent.h"
#include "components/physicscomponent.h"
#include "components/ballcomponent.h"

#include "GameObject.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "SpriteSheet.h"

#include "Layer.h"

ComponentFactory::ComponentFactory(b2World* p_world, yam2d::TmxMap* p_map) :
    yam2d::DefaultComponentFactory(),
    m_ballTexture(new yam2d::Texture("assets/textures/ball.png")),
    m_paddleTexture(new yam2d::Texture("assets/textures/paddle.png")),
    m_fontTexture(new yam2d::Texture("assets/textures/Fixedsys_24_Bold.png")),
    m_font(yam2d::SpriteSheet::autoFindFontFromTexture(m_fontTexture, "assets/fonts/Fixedsys_24_Bold.dat")),
    m_world(p_world),
    m_map(p_map)
{
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

		b2BodyDef b;
		b.type = b2_staticBody;
		b.position = p_gameObject->getPosition();

		b2Body* p_body = m_world->CreateBody(&b);

        b2PolygonShape shape;

        b2Vec2 vertices[6];

        vertices[0].Set(0.5f, 0.0f);
        vertices[1].Set(0.25f, 0.5f);
        vertices[2].Set(-0.25f, 0.5f);
        vertices[3].Set(-0.5f, 0.0f);
        vertices[4].Set(-0.25f, -0.5f);
        vertices[5].Set(0.25f, -0.5f);

        shape.Set(vertices, 6);

        b2FixtureDef fixture;
        fixture.shape = &shape;
        fixture.density = 1;
        fixture.restitution = 1.0f;
		fixture.friction = 1.0f;
        p_body->CreateFixture(&fixture);
        p_body->SetUserData(p_gameObject);

		p_gameObject->addComponent(new PhysicsComponent(p_gameObject, m_world, p_body));

        return p_gameObject;
    }
    else if (type == "Ball")
    {
        yam2d::GameObject* p_gameObject = new yam2d::GameObject(nullptr, 0);
        p_gameObject->setType(type);

        p_gameObject->addComponent(new yam2d::SpriteComponent(p_gameObject, m_ballTexture));

		p_gameObject->getComponent<yam2d::SpriteComponent>()->setRenderingEnabled(true);

        b2BodyDef b;
        b.type = b2_kinematicBody;
        b.bullet = true;
		b.fixedRotation = true;

        b2Body* p_body = m_world->CreateBody(&b);

        b2CircleShape shape;
        shape.m_radius = 0.25f;

        b2FixtureDef fixture;
        fixture.shape = &shape;
        fixture.density = 1.0f;
        fixture.restitution = 1.0f;
        fixture.friction = 1.0f;

        p_body->CreateFixture(&fixture);
        p_body->SetTransform(b2Vec2(8.0f, m_map->getHeight() / 2.0f), 0.0f);
        p_body->SetUserData(p_gameObject);

        p_gameObject->addComponent(new PhysicsComponent(p_gameObject, m_world, p_body));
        p_gameObject->addComponent(new BallComponent(p_gameObject, m_map));

        m_map->getLayer("GameObjects")->addGameObject(p_gameObject);

        return p_gameObject;
    }
    else if (type == "Paddle")
    {
        yam2d::GameObject* p_gameObject = new yam2d::GameObject(nullptr, 0);
        p_gameObject->setType(type);

        p_gameObject->addComponent(new yam2d::SpriteComponent(p_gameObject, m_paddleTexture));
        p_gameObject->addComponent(new PaddleComponent(p_gameObject, m_map));

		p_gameObject->getComponent<yam2d::SpriteComponent>()->setRenderingEnabled(true);

		b2BodyDef b;
		b.type = b2_kinematicBody;

		b2Body* p_body = m_world->CreateBody(&b);

		b2PolygonShape shape;
        shape.SetAsBox(
            (p_gameObject->getSize().x / m_map->getTileWidth()) / 2.0f, 
            (p_gameObject->getSize().y / m_map->getTileHeight()) / 2.0f);

		b2FixtureDef fixture;
        fixture.shape = &shape;
        fixture.density = 1;
        fixture.restitution = 1.0f;
		fixture.friction = 1.0f;
        p_body->CreateFixture(&fixture);
        p_body->SetTransform(b2Vec2(2.5f, -8.0f), 0.0f);
        p_body->SetUserData(p_gameObject);
        
		p_gameObject->addComponent(new PhysicsComponent(p_gameObject, m_world, p_body));

        m_map->getLayer("GameObjects")->addGameObject(p_gameObject);

        return p_gameObject;
    }
	else if (type == "Label")
	{
		yam2d::GameObject* p_gameObject = new yam2d::GameObject(nullptr, 0);
		p_gameObject->setType(type);

		p_gameObject->addComponent(new yam2d::TextComponent(p_gameObject, m_font));

		m_map->getLayer("GameObjects")->addGameObject(p_gameObject);

		return p_gameObject;
	}

    return yam2d::DefaultComponentFactory::createNewEntity(p_componentFactory, type, p_parent, properties);
}