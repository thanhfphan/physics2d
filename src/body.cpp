#include "body.h"
#include "log.h"
#include "const.h"
#include "shape.h"

Body::Body(Shape *shape, float x, float y, float m)
{
	position = Vec2(x, y);

	mass = m;
	invMass = m != 0.0f ? 1.0 / mass : 0.0f;

	I = shape->GetMomentOfInertia() * mass;
	invI = I != 0.0f ? 1.0 / I : 0.0f;

	totalForce = Vec2();
	velocity = Vec2();
	acceleration = Vec2();

	rotation = 0.0f;
	angularVelocity = 0.0f;
	angularAcceleration = 0.0f;
	sumTorque = 0.0f;

	this->shape = shape;
	Log::Info("body constructor has called");
}

Body::~Body()
{
	delete shape;
	Log::Info("body destructor has called");
}
void Body::AddForce(Vec2 &force)
{
	totalForce += force;
}
void Body::AddTorque(float torque){
	sumTorque += torque;
}

void Body::ClearForce()
{
	totalForce = Vec2();
}

void Body::ClearTorque()
{
	sumTorque = 0;
}

void Body::IntegrateLinear(const float dt)
{
	acceleration = totalForce * invMass;
	velocity += acceleration * dt;
	position += velocity * dt;
	ClearForce();
}

void Body::IntegrateAngular(const float dt)
{
	angularVelocity = sumTorque * invI;
	angularVelocity += angularAcceleration * dt;
	rotation += angularVelocity * dt;
	ClearTorque();
}

void Body::Update(const float dt)
{
	IntegrateLinear(dt);
	IntegrateAngular(dt);
	if (this->shape->GetType() == "polygon")
	{
		Polygon *polygon = (Polygon *)this->shape;
		polygon->UpdateVertices(this->position);
	}
}
