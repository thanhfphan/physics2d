#pragma once

#include "string"

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
	Polygon();
	~Polygon();
	std::string GetType()
	{
		return "polygon";
	}
};
