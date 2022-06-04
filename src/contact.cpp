#include "contact.h"

void Contact::ResolvePenetration()
{
	float da = depth * b->mass / (a->mass + b->mass);
	float db = depth * a->mass / (a->mass + b->mass);

	a->position -= normal * da;
	b->position += normal * db;
}

void Contact::ResolveCollision()
{
	Body *a = this->a;
	Body *b = this->b;

	float elasticity = std::min(a->restitution, b->restitution);
	Vec2 vrel = a->velocity - b->velocity;
	float impulseMagnitude = vrel.Dot(this->normal) * -(1 + elasticity) / (a->invMass + b->invMass);
	Vec2 jn = this->normal * impulseMagnitude;

	a->ApplyImpulse(jn);
	b->ApplyImpulse(-jn);
}