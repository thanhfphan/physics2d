#pragma once

#include "shape.h"
#include "vec2.h"

struct Body
{
	Body(Shape* shape, float x, float y, float mass);
	~Body();

	float mass;
	float invMass;
	float I;
	float invI;

	float restitution;
	float friction;

	Vec2 totalForce;

	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;

	float rotation;
	float angularVelocity;
	float angularAcceleration;
	float sumTorque;

	Shape* shape;

	void AddForce(Vec2& force);
	void AddTorque(float torque);
	void ClearForce();
	void ClearTorque();
	void IntegrateLinear(const float dt);
	void IntegrateAngular(const float dt);
	void Update(const float dt);
	bool IsStatic() const;
	void ApplyImpulse(const Vec2 j);
	void ApplyImpulse(const Vec2 j, const Vec2 r);
};
