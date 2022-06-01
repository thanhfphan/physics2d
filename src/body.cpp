#include "body.h"
#include "log.h"
#include "const.h"

Body::Body(float x, float y, float m)
{
	Log::Info("body constructor has called");
	position = Vec2(x, y);
	mass = m;

	totalForce = Vec2();
	velocity = Vec2();
	acceleration = Vec2();
	shape = NULL;
}

Body::~Body()
{
	Log::Info("body destructor has called");
}
void Body::AddForce(Vec2 &force)
{
	totalForce += force;
}

void Body::ClearForce()
{
	totalForce = Vec2();
}

void Body::Integrate(const float dt)
{
	acceleration = (totalForce / mass) * METER_PER_PIXEL;
	velocity += acceleration * dt;
	position += velocity * dt;
}
void Body::Update(const float dt)
{
	Integrate(dt);
	if (this->shape->GetType() == "polygon")
	{
		Polygon *polygon = (Polygon *)this->shape;
		polygon->UpdateVertices(this->position);
	}
}
