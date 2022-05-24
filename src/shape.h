#pragma once

#include <vector>
#include "string"
#include "vec2.h"

struct Shape
{
	Shape(){}
	~Shape(){}
	virtual std::string GetType() = 0;
};

struct Circle : public Shape
{
	int radius;

	Circle(int r)
	{
		this->radius = r;
	}
	~Circle() {}
	std::string GetType()
	{
		return "circle";
	}
};

struct Polygon : public Shape
{
	std::vector<Vec2> vertices;
	Polygon(std::vector<Vec2> vertices){
		this->vertices = vertices;
	}
	~Polygon(){}
	std::string GetType()
	{
		return "polygon";
	}
};
