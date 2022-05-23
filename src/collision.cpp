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

	Vec2 tmp = Vec2(a->position.x - b->position.x,a->position.y - b->position.y);
	double distance = sqrt(tmp.x*tmp.x + tmp.y*tmp.y);

	if (distance < (ca->radius + cb->radius)){
		return true;
	}

	return false;
}