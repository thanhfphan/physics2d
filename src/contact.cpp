#include "contact.h"
#include "TK/Log.h"

void Contact::ResolvePenetration()
{
	if (a->IsStatic() && b->IsStatic())
	{
		return;
	}

	float da = depth / (a->invMass + b->invMass) * a->invMass;
	float db = depth / (a->invMass + b->invMass) * b->invMass;

	a->position -= normal * da;
	b->position += normal * db;

	a->shape->UpdateVertices(a->position, a->rotation);
	b->shape->UpdateVertices(b->position, b->rotation);
}

void Contact::ResolveCollision()
{
	ResolvePenetration();

	Body *a = this->a;
	Body *b = this->b;

	float elasticity = std::min<float>(a->restitution, b->restitution);
	float f = std::min<float>(a->friction, b->friction);

	Vec2 ra = this->end - a->position;
	Vec2 rb = this->start - b->position;
	Vec2 va = a->velocity + Vec2(-a->angularVelocity * ra.y, a->angularVelocity * ra.x);
	Vec2 vb = b->velocity + Vec2(-b->angularVelocity * rb.y, b->angularVelocity * rb.x);

	float impulseMagnitude = (va - vb).Dot(this->normal) * (-1 - elasticity) / (a->invMass + b->invMass + ra.Cross(this->normal) * ra.Cross(this->normal) * a->invI + rb.Cross(this->normal) * rb.Cross(this->normal) * b->invI);
	Vec2 jn = this->normal * impulseMagnitude;

	Vec2 tangent = this->normal.Normal();
	float impulseMagnitudeT = (va - vb).Dot(tangent) * f * (-1 - elasticity) / (a->invMass + b->invMass + ra.Cross(tangent) * ra.Cross(tangent) * a->invI + rb.Cross(tangent) * rb.Cross(tangent) * b->invI);
	Vec2 jt = tangent * impulseMagnitudeT;

	Vec2 j = jt + jn;
	a->ApplyImpulse(j, ra);
	b->ApplyImpulse(-j, rb);
}