#pragma once

#include "shape.h"
#include "vec2.h"

struct Body
{
	Body();
	~Body();
	Vec2 totalForce;
	Vec2 position;
	Vec2 velocity;
	Shape* shape;

	void AddForce(Vec2& force);
	void ClearForce();
	void Movement(const float dt);
};
