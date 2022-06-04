#include "collision.h"
#include "log.h"
#include "vec2.h"
#include <math.h>
#include <limits>
#include <iostream>

bool Collision::IsColliding(Body *a, Body *b, Contact &contact)
{
	if (!a->shape || !b->shape)
	{
		Log::Error("can't check collison between pylygon vs polygon because shape is null");
		return false;
	}

	std::string aType = a->shape->GetType();
	std::string bType = b->shape->GetType();

	if (aType == "circle" && bType == "circle")
	{
		return CircleToCircle(a, b, contact);
	}
	else if (aType == "polygon" && bType == "polygon")
	{
		return PolygonToPylygon(a, b, contact);
	}

	Log::Error("IsColliding between " + aType + " vs " + bType + " is not supported");

	return false;
}

bool Collision::CircleToCircle(Body *a, Body *b, Contact &contact)
{
	Circle *ca = static_cast<Circle *>(a->shape);
	Circle *cb = static_cast<Circle *>(b->shape);

	Vec2 distance = b->position - a->position;
	float radiusSum = ca->radius + cb->radius;

	bool isCollide = distance.MagnitudeSquared() < (radiusSum * radiusSum);
	if (!isCollide)
	{
		return false;
	}

	contact.a = a;
	contact.b = b;
	Vec2 ab = b->position - a->position;
	contact.normal = ab.UnitVector();
	contact.start = b->position - contact.normal * cb->radius;
	contact.end = a->position + contact.normal * ca->radius;
	contact.depth = (contact.end - contact.start).Magnitude();

	return true;
}

bool Collision::PolygonToPylygon(Body *a, Body *b, Contact &contact)
{
	Polygon *pa = static_cast<Polygon *>(a->shape);
	Polygon *pb = static_cast<Polygon *>(b->shape);

	float separation = std::numeric_limits<float>::lowest();
	for (int i = 0; i < pa->worldVertices.size(); i++)
	{
		Vec2 va = pa->worldVertices[i];
		Vec2 normal = pa->GetEdge(i).Normal();
		float minStep = std::numeric_limits<float>::max();
		for (int j = 0; j < pb->worldVertices.size(); j++)
		{
			Vec2 vb = pb->worldVertices[j];
			float proj = (vb - va).Dot(normal);
			minStep = std::min(minStep, proj);
		}
		separation = std::max(separation, minStep);
	}
	return separation < 0;
}