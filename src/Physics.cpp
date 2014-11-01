#include <Antic/Physics.h>

b2World* antic::world = nullptr;

b2Body* antic::createBodyStatic(  float x, float y, float w, float h )
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set( x + w/2.f, y + h/2.f );

	b2PolygonShape groundBox;
	groundBox.SetAsBox( w/2.f, h/2.f );

	b2Body* body = antic::world->CreateBody( &groundBodyDef );
	body->CreateFixture( &groundBox, 0.0f );

	return body;
}

b2Body* antic::createBodyDynamic( float x, float y, float w, float h, float density, float friction )
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set( x, y );

	b2Body* body = antic::world->CreateBody( &bodyDef );

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox( w/2.f, h/2.f );

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = density;
	fixtureDef.friction = friction;

	body->CreateFixture( &fixtureDef );

	return body;
}