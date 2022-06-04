#pragma once

#include "body.h"

struct Contact
{
	Body *a,*b;

	Vec2 start, end;
	Vec2 normal;

	float depth;
	Contact() = default;
	~Contact() = default;

	void ResolvePenetration();
	void ResolveCollision();
};
