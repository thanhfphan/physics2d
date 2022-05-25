#pragma once
#include "vec2.h"
#include "body.h"

struct Force
{
	static Vec2 GenWeightForce(const Body* body, float g){
		return Vec2(0, body->mass*g);
	}

	static Vec2 GenDragForce(const Body* body, float k){
		Vec2 direction = body->velocity.UnitVector() * -1.0;
		float magnitude = k * body->velocity.MagnitudeSquared();

		return direction * magnitude;
	}

	static Vec2 GenFrictionForce(const Body* body, float magnitude){
		Vec2 direction = (body->velocity.UnitVector() * -1.0);
		
		return direction * magnitude;
	}
};
