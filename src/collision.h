#pragma once

#include "shape.h"
#include "body.h"

class Collision
{
public:
	static bool CircleToCircle(Body *a, Body *b);
	static bool PolygonToPylygon(Body *a, Body *b);
};