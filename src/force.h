#pragma once
#include "vec2.h"
#include "body.h"

struct Force
{
	static Vec2 GenWeightForce(const Body *body, float g)
	{
		return Vec2(0, body->mass * g);
	}

	static Vec2 GenDragForce(const Body *body, float k)
	{
		Vec2 direction = body->velocity.UnitVector() * -1.0;
		float magnitude = k * body->velocity.MagnitudeSquared();

		return direction * magnitude;
	}

	static Vec2 GenFrictionForce(const Body *body, float magnitude)
	{
		Vec2 direction = (body->velocity.UnitVector() * -1.0);

		return direction * magnitude;
	}

	static Vec2 GenGravitationalAttraction(const Body *a, const Body *b, float g)
	{
		Vec2 d = (b->position - a->position);
		Vec2 direction = d.UnitVector();

		float distance = d.MagnitudeSquared();
		if (distance < 5){
			distance = 5;
		}else if (distance > 100){
			distance = 100;
		}

		return direction* g * (a->mass * b->mass)/ distance;
	}

	static Vec2 GenSpringForce(const Body *a, Vec2 anchor, float restLength, float k){
		Vec2 d = a->position - anchor;

		float deltaL = d.Magnitude() - restLength;
		Vec2 direction = d.UnitVector();

		return direction * -k * deltaL;
	}
};
