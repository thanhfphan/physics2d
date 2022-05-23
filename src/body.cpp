#include "body.h"
#include "log.h"

Body::Body()
{
	Log::Info("body constructor has called");
	this->totalForce = Vec2();
	this->position = Vec2();
	this->shape = NULL;
}

Body::~Body()
{
	Log::Info("body destructor has called");
	// delete this->shape;
}
void Body::AddForce(Vec2 &force)
{
	totalForce.x = totalForce.x + force.x;
	totalForce.y = totalForce.y + force.y;
}

void Body::ClearForce()
{
	this->totalForce = Vec2();
}