#include "shape.h"
#include "log.h"

/*
*
* ------------------- Circle --------------------
*
*/
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

void Circle::UpdateVertices(Vec2 position, float angle)
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

/*
*
* ------------------- Box --------------------
*
*/
Box::Box(int width, int height)
{
	this->width = width;
	this->height = height;
	localVertices.push_back(Vec2(-width/2, height/2));
	localVertices.push_back(Vec2(-width/2, -height/2));
	localVertices.push_back(Vec2(width/2, -height/2));
	localVertices.push_back(Vec2(width/2, height/2));

	worldVertices.push_back(Vec2(-width/2, height/2));
	worldVertices.push_back(Vec2(-width/2, -height/2));
	worldVertices.push_back(Vec2(width/2, -height/2));
	worldVertices.push_back(Vec2(width/2, height/2));
	Log::Info("box constructor has called");
}
Box::~Box()
{
	Log::Info("box destructor has called");
}

std::string Box::GetType() const
{
	return "box";
}
void Box::UpdateVertices(Vec2 position, float angle)
{
	for (int i = 0; i < localVertices.size(); i++)
	{
		worldVertices[i] = localVertices[i].Rotate(angle);
		worldVertices[i] += position;
	}
}
float Box::GetMomentOfInertia() const
{
	// 1/12 * (w^2 + h^2) * mass
	return 0.08333 * (width * width + height * height);
}
Shape *Box::Clone() const
{
	return new Box(width, height);
};

Vec2 Box::GetEdge(int index) const{
	int nextIndex = (index + 1) % worldVertices.size();
	return worldVertices[nextIndex] - worldVertices[index];
}

/*
*
* ------------------- Polygon --------------------
*
*/
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

void Polygon::UpdateVertices(Vec2 position, float angle)
{
	for (int i = 0; i < localVertices.size(); i++)
	{
		worldVertices[i] = localVertices[i].Rotate(angle);
		worldVertices[i] += position;
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