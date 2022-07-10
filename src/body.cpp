#include "body.h"
#include "TK/Log.h"
#include "const.h"
#include "shape.h"
#include <math.h>

Body::Body(Shape *shape, float x, float y, float m)
{
	position = Vec2(x, y);

	mass = m;
	invMass = m != 0.0f ? 1.0 / mass : 0.0f;

	I = shape->GetMomentOfInertia() * mass;
	invI = I != 0.0f ? 1.0 / I : 0.0f;

	restitution = 1.0f;

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
void Body::AddTorque(float torque)
{
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
	if (IsStatic())
	{
		return;
	}

	acceleration = totalForce * invMass;
	velocity += acceleration * dt;
	position += velocity * dt;

	ClearForce();
}

void Body::IntegrateAngular(const float dt)
{
	if (IsStatic())
	{
		return;
	}

	angularAcceleration= sumTorque * invI;
	angularVelocity += angularAcceleration * dt;
	rotation += angularVelocity * dt;

	ClearTorque();
}

void Body::Update(const float dt)
{
	IntegrateLinear(dt);
	IntegrateAngular(dt);
	shape->UpdateVertices(this->position, this->rotation);
}

bool Body::IsStatic() const
{
	const float epsilon = 0.005f;
	return fabs(invMass - 0.0f) < epsilon;
}

void Body::ApplyImpulse(const Vec2 j)
{
	if (IsStatic())
	{
		return;
	}

	velocity += j * invMass;
}

void Body::ApplyImpulse(const Vec2 j, const Vec2 r)
{
	if (IsStatic())
	{
		return;
	}

	velocity += j * invMass;
	angularVelocity += r.Cross(j) * invI;
}
