#pragma once

#include <vector>
#include "string"
#include "vec2.h"

struct Shape
{
	Shape(){}
	~Shape(){}
	virtual std::string GetType() = 0;
	// convert local vertices to world vertices
	virtual void UpdateVertices(Vec2 position) = 0;
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

	void UpdateVertices(Vec2 position){
		return;
	}
};

struct Polygon : public Shape
{
	std::vector<Vec2> localVertices;
	std::vector<Vec2> worldVertices;

	Polygon(std::vector<Vec2> localVertices){
		this->localVertices = localVertices;
		this->worldVertices = localVertices;
	}

	~Polygon(){}
	
	std::string GetType()
	{
		return "polygon";
	}

	void UpdateVertices(Vec2 position){
		for(int i=0; i< localVertices.size(); i ++){
			worldVertices[i] = localVertices[i] + position;
		}
	}

	Vec2 GetEdge(int index){
		int nextIndex = (index + 1) % worldVertices.size();
		return worldVertices[nextIndex] - worldVertices[index];
	}
};
