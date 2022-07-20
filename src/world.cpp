#include "world.h"
#include "force.h"
#include "const.h"
#include "contact.h"
#include "collision.h"

World::World(float gravity)
{
	this->gravity = gravity;
}

World::~World()
{
	for (auto b : bodies)
	{
		delete b;
	}
}

Body *World::CreateBody(Body *b)
{
	this->bodies.push_back(b);
	return b;
}

void World::DestroyBody(Body *b)
{
}

std::vector<Body *> World::GetBodies()
{
	return bodies;
}

void World::ClearForces()
{
	for (auto b : bodies)
	{
		b->ClearForce();
	}
}

void World::ClearTorques()
{
	for (auto b : bodies)
	{
		b->ClearTorque();
	}
}

void World::AddForce(Vec2 &force)
{
	for (auto b : bodies)
	{
		b->AddForce(force);
	}
}

void World::AddTorque(float torque)
{
	for (auto b : bodies)
	{
		b->AddTorque(torque);
	}
}

void World::Step(float dt)
{
	for (auto b : bodies)
	{
		Vec2 weightForce = Force::GenWeightForce(b, this->gravity* METER_PER_PIXEL);
		b->AddForce(weightForce);

		// float torque = 10.0 * METER_PER_PIXEL;
		// body->AddTorque(torque);
	}

	for (auto b : bodies)
	{
		b->Update(dt);
	}

	for (size_t i = 0; i < bodies.size() - 1; i++)
	{
		for (size_t j = i + 1; j < bodies.size(); j++)
		{
			Contact contact;
			Body *a = bodies[i];
			Body *b = bodies[j];
			if (Collision::IsColliding(a, b, contact))
			{
				contact.ResolveCollision();
			}
		}
	}
}