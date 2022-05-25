#pragma once

#include "shape.h"
#include "vec2.h"

struct Body
{
	Body(float x, float y, float mass);
	~Body();

	float mass;

	Vec2 totalForce;
	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;
	Shape* shape;

	void AddForce(Vec2& force);
	void ClearForce();
	void Integrate(const float dt);
};
