#pragma once

#include "shape.h"
#include "body.h"
#include "contact.h"

class Collision
{
public:
	static bool IsColliding(Body *a, Body *b, Contact &contact);
	static bool CircleToCircle(Body *a, Body *b, Contact &contact);
	static bool PolygonToPylygon(Body *a, Body *b, Contact &contact);
};