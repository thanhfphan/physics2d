#include "collision.h"
#include "TK/Log.h"
#include "vec2.h"
#include <math.h>
#include <limits>
#include <iostream>

bool Collision::IsColliding(Body *a, Body *b, Contact &contact)
{
	if (a->IsStatic() && b->IsStatic())
	{
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

	float separationAB = std::numeric_limits<float>::lowest();
	Vec2 normalAB;
	Vec2 pointAB;
	for (size_t i = 0; i < pa->worldVertices.size(); i++)
	{
		Vec2 vi = pa->worldVertices[i];
		Vec2 normal = pa->GetEdge(i).Normal();
		float minStep = std::numeric_limits<float>::max();
		Vec2 minV;
		for (size_t j = 0; j < pb->worldVertices.size(); j++)
		{
			Vec2 vj = pb->worldVertices[j];
			float proj = (vj - vi).Dot(normal);
			if (proj < minStep)
			{
				minStep = proj;
				minV = vj;
			}
		}
		if (minStep > separationAB)
		{
			separationAB = minStep;
			normalAB = normal;
			pointAB = minV;
		}
	}
	if (separationAB >= 0)
	{
		return false;
	}

	float separationBA = std::numeric_limits<float>::lowest();
	Vec2 normalBA;
	Vec2 pointBA;
	for (size_t i = 0; i < pb->worldVertices.size(); i++)
	{
		Vec2 vi = pb->worldVertices[i];
		Vec2 normal = pb->GetEdge(i).Normal();
		float minStep = std::numeric_limits<float>::max();
		Vec2 minV;
		for (size_t j = 0; j < pa->worldVertices.size(); j++)
		{
			Vec2 vj = pa->worldVertices[j];
			float proj = (vj - vi).Dot(normal);
			if (proj < minStep)
			{
				minStep = proj;
				minV = vj;
			}
		}
		if (minStep > separationBA)
		{
			separationBA = minStep;
			normalBA = normal;
			pointBA = minV;
		}
	}
	if (separationBA >= 0)
	{
		return false;
	}

	if (separationAB > separationBA)
	{
		contact.depth = -separationAB;
		contact.normal = normalAB;
		contact.start = pointAB;
		contact.end = pointAB + contact.normal * contact.depth;
	}
	else
	{
		contact.depth = -separationBA;
		contact.normal = -normalBA;
		contact.start = pointBA - contact.normal * contact.depth;
		contact.end = pointBA;
	}
	contact.a = a;
	contact.b = b;

	return true;
}
