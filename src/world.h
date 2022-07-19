#pragma once

#include "body.h"
#include "vec2.h"

class World{
private:
	float gravity;
	std::vector<Body*> bodies;

public:
	World(float gravity);
	~World();
	Body* CreateBody(Body *b);
	void DestroyBody(Body *b);
	std::vector<Body*> GetBodies();
	void ClearForces();
	void ClearTorques();
	void AddForce(Vec2& force);
	void AddTorque(float torque);
	void Step(float dt);
};