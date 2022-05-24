#include "collision.h"
#include "log.h"
#include "vec2.h"
#include <math.h>

bool CircleToCircle(Body* a, Body* b){
	if (a->shape->GetType() != "circle" || b->shape->GetType() != "circle"){
		Log::Error("wrong type");
		return false;
	}

	Circle* ca = static_cast<Circle*>(a->shape);
	Circle* cb = static_cast<Circle*>(b->shape);

	Vec2 distance = b->position - a->position;
	if (distance.Magnitude() < (ca->radius + cb->radius)){
		return true;
	}

	return false;
}