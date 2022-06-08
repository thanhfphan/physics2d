#include "contact.h"
#include "log.h"

void Contact::ResolvePenetration()
{
	if (a->IsStatic() && b->IsStatic())
	{
		return;
	}
	float da = depth * b->mass / (a->mass + b->mass);
	float db = depth * a->mass / (a->mass + b->mass);

	if (!a->IsStatic())
	{
		a->position -= normal * da;
	}
	if (!a->IsStatic())
	{
		b->position += normal * db;
	}
}

void Contact::ResolveCollision()
{
	ResolvePenetration();

	Body *a = this->a;
	Body *b = this->b;

	float elasticity = std::min<float>(a->restitution, b->restitution);
	Vec2 vrel = a->velocity - b->velocity;
	float impulseMagnitude = vrel.Dot(this->normal) * -(1 + elasticity) / (a->invMass + b->invMass);
	Vec2 jn = this->normal * impulseMagnitude;

	a->ApplyImpulse(jn);
	b->ApplyImpulse(-jn);
}