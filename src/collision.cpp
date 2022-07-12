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

	bool aIsCircle = a->shape->GetType() == "circle";
	bool bIsCircle = b->shape->GetType() == "circle";
	bool aIsPolygon = a->shape->GetType() == "polygon";
	bool bIsPolygon = b->shape->GetType() == "polygon";

	if (aIsCircle && bIsCircle)
	{
		return CircleToCircle(a, b, contact);
	}
	else if (aIsPolygon && bIsPolygon)
	{
		return PolygonToPylygon(a, b, contact);
	}
	else if (aIsPolygon && bIsCircle)
	{
		return PolygonToCircle(a, b, contact);
	}
	else if (aIsCircle && bIsPolygon)
	{
		return PolygonToCircle(b, a, contact);
	}

	Log::Error("IsColliding between " + a->shape->GetType() + " vs " + b->shape->GetType() + " is not supported");

	return false;
}

bool Collision::PolygonToCircle(Body *a, Body *b, Contact &contact)
{
	Polygon *polygon = static_cast<Polygon *>(a->shape);
	Circle *circle = static_cast<Circle *>(b->shape);

	size_t index = 0;
	float distance = 0.0f;
	float minD = std::numeric_limits<float>::max();
	bool isOutside = false;
	size_t indexI = 0;
	float distanceI = 0.0f;
	float maxDI = std::numeric_limits<float>::lowest();
	
	for (size_t i = 0; i < polygon->worldVertices.size(); i++)
	{
		Vec2 normal = polygon->GetEdge(i).Normal();
		float d = (b->position - polygon->worldVertices[i]).Dot(normal);
		if (d > 0 && d < minD)
		{
			index = i;
			distance = d;
			minD = d;
			isOutside = true;
		}else {
			if (d > maxDI){
				maxDI = d;
				indexI = i;
				distanceI = d*-1;
			}
		}
	}

	if (isOutside)
	{
		size_t nextIndex = (index + 1) % polygon->worldVertices.size();
		Vec2 edge = polygon->GetEdge(index);
		float l = edge.UnitVector().Dot(b->position - polygon->worldVertices[index]);
		if (l < 0)
		{
			float dp2e = (b->position - polygon->worldVertices[index]).Magnitude();
			if (circle->radius < dp2e)
			{
				return false;
			}
			contact.depth = circle->radius - dp2e;
			contact.normal = (b->position - polygon->worldVertices[index]).UnitVector();
			contact.start = b->position - contact.normal * circle->radius;
			contact.end = b->position - contact.normal * (circle->radius - contact.depth);
		}
		else if (l > edge.Magnitude())
		{
			float dp2ne = (b->position - polygon->worldVertices[nextIndex]).Magnitude();
			if (circle->radius < dp2ne)
			{
				return false;
			}
			contact.depth = circle->radius - dp2ne;
			contact.normal = (b->position - polygon->worldVertices[nextIndex]).UnitVector();
			contact.start = b->position - contact.normal * circle->radius;
			contact.end = b->position - contact.normal * (circle->radius - contact.depth);
		}
		else
		{
			if (circle->radius < distance)
			{
				return false;
			}
			contact.depth = circle->radius - distance;
			contact.normal = edge.Normal();
			contact.start = b->position - (contact.normal * circle->radius);
			contact.end = b->position - (contact.normal * (circle->radius - contact.depth));
		}
	}
	else
	{
			contact.depth = distanceI;
			contact.normal = polygon->GetEdge(indexI).Normal();
			contact.start = b->position - (contact.normal * circle->radius);
			contact.end = contact.start + contact.normal * (circle->radius + contact.depth);
	}

	contact.a = a;
	contact.b = b;

	return true;
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

	contact.a = a;
	contact.b = b;
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

	return true;
}
