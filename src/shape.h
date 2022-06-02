#pragma once

#include <vector>
#include "string"
#include "vec2.h"

struct Shape
{
	virtual ~Shape() = default;
	virtual std::string GetType() const = 0;
	// convert local vertices to world vertices
	virtual void UpdateVertices(Vec2 position, float angle) = 0;
	virtual float GetMomentOfInertia() const = 0; // note: without mass
	virtual Shape *Clone() const = 0;
};
struct Circle : public Shape
{
	int radius;

	Circle(int r);
	virtual ~Circle();

	std::string GetType() const override;
	void UpdateVertices(Vec2 position, float angle) override;
	float GetMomentOfInertia() const override;
	Shape *Clone() const override;
};

struct Box : public Shape
{
	std::vector<Vec2> localVertices, worldVertices;
	int width, height;

	Box(int width, int height);
	virtual ~Box();

	std::string GetType() const override;
	void UpdateVertices(Vec2 position, float angle) override;
	float GetMomentOfInertia() const override;
	Shape *Clone() const override;

	Vec2 GetEdge(int index) const;
};


struct Polygon : public Shape
{
	std::vector<Vec2> localVertices, worldVertices;

	Polygon(std::vector<Vec2> localVertices);
	virtual ~Polygon();

	std::string GetType() const override;
	float GetMomentOfInertia() const override;
	void UpdateVertices(Vec2 position, float angle) override;
	Shape *Clone() const override;

	Vec2 GetEdge(int index) const;
};
