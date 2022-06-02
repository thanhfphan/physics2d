#include "shape.h"
#include "log.h"

// Circle
Circle::Circle(int r)
{
	this->radius = r;
	Log::Info("circle constructor has called");
}

Circle::~Circle()
{
	Log::Info("circle destructor has called");
}

std::string Circle::GetType() const
{
	return "circle";
}

void Circle::UpdateVertices(Vec2 position)
{
	return;
}

// note: without mass
float Circle::GetMomentOfInertia() const
{
	return 0.5 * radius * radius;
}

Shape *Circle::Clone() const
{
	return new Circle(radius);
}
// End Circle

// Polygon
Polygon::Polygon(std::vector<Vec2> localVertices)
{
	this->localVertices = localVertices;
	this->worldVertices = localVertices;
	Log::Info("polygon constructor has called");
}

Polygon::~Polygon()
{
	Log::Info("polygon destructor has called");
}

std::string Polygon::GetType() const
{
	return "polygon";
}

// note: without mass
float Polygon::GetMomentOfInertia() const
{
	return 0.08 * 50 * 50 + 100 * 100; //FIXME: remove hardcode
}

void Polygon::UpdateVertices(Vec2 position)
{
	for (int i = 0; i < localVertices.size(); i++)
	{
		worldVertices[i] = localVertices[i] + position;
	}
}

Vec2 Polygon::GetEdge(int index) const
{
	int nextIndex = (index + 1) % worldVertices.size();
	return worldVertices[nextIndex] - worldVertices[index];
}

Shape *Polygon::Clone() const
{
	return new Polygon(localVertices);
}
// End Polygon