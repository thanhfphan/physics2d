#include "collision.h"
#include "log.h"
#include "vec2.h"
#include <math.h>
#include <limits>
#include <iostream>

bool Collision::CircleToCircle(Body *a, Body *b)
{
	if (!a->shape || !a->shape)
	{
		Log::Error("can't check collison between pylygon vs polygon because shape is null");
		return false;
	}
	if (a->shape->GetType() != "circle" || b->shape->GetType() != "circle")
	{
		Log::Error("can't check collison between circle vs circle because wrong type");
		return false;
	}

	Circle *ca = static_cast<Circle *>(a->shape);
	Circle *cb = static_cast<Circle *>(b->shape);

	Vec2 distance = b->position - a->position;
	if (distance.Magnitude() < (ca->radius + cb->radius))
	{
		return true;
	}

	return false;
}
bool Collision::PolygonToPylygon(Body *ba, Body *bb)
{
	if (!ba->shape || !ba->shape)
	{
		Log::Error("can't check collison between pylygon vs polygon because shape is null");
		return false;
	}
	if (ba->shape->GetType() != "polygon" || bb->shape->GetType() != "polygon")
	{
		Log::Error("can't check collison between pylygon vs polygon because wrong type");
		return false;
	}

	Polygon *a = static_cast<Polygon *>(ba->shape);
	Polygon *b = static_cast<Polygon *>(bb->shape);

	float separation = std::numeric_limits<float>::lowest();
	for (int i = 0; i < a->worldVertices.size(); i++)
	{
		Vec2 va = a->worldVertices[i];
		Vec2 normal = a->GetEdge(i).Normal();
		float minStep = std::numeric_limits<float>::max();
		for (int j = 0; j < b->worldVertices.size(); j++)
		{
			Vec2 vb = b->worldVertices[j];
			float proj = (vb - va).Dot(normal);
			minStep = std::min(minStep, proj);
		}
		separation = std::max(separation, minStep);
		Log::Debug("separation " + std::to_string(separation));
	}
	Log::Debug("----------------");
	return separation < 0;
}