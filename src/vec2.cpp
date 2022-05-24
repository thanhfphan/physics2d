#include "vec2.h"
#include "math.h"

Vec2::Vec2()
{
	x = 0;
	y = 0;
}

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2 Vec2::operator+(const Vec2 &v) const
{
	return Vec2(this->x + v.x, this->y + v.y);
}

Vec2 Vec2::operator-(const Vec2 &v) const
{
	return Vec2(this->x - v.x, this->y - v.y);
}

Vec2 Vec2::operator*(const float n) const
{
	return Vec2(this->x * n, this->y * n);
}

Vec2 Vec2::operator/(const float n) const
{
	if (n == 0.0)
	{
		return Vec2();
	}

	return *this * (1 / n);
}

Vec2 &Vec2::operator+=(const Vec2 &v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vec2 &Vec2::operator*=(const float n)
{
	this->x *= n;
	this->y *= n;
	return *this;
}

Vec2 &Vec2::operator/=(const float n)
{
	return *this *= (1 / n);
}

Vec2 Vec2::Rotate(const float angle) const
{
	Vec2 result;
	result.x = this->x * cos(angle) - this->y * sin(angle);
	result.y = this->x * sin(angle) + this->y * cos(angle);
	return result;
}

Vec2 &Vec2::Normalize()
{
	float length = this->Magnitude();
	if (length != 0)
	{
		this->x /= length;
		this->y /= length;
	}

	return *this;
}
Vec2 Vec2::UnitVector() const
{
	Vec2 result;
	float length = this->Magnitude();
	if (length != 0)
	{
		result.x = this->x / length;
		result.y = this->y / length;
	}

	return result;
}

Vec2 Vec2::Normal() const
{
	return Vec2(this->y, -this->x).Normalize();
}

void Vec2::Scale(const float n)
{
	this->x *= n;
	this->y *= n;
}

float Vec2::Dot(const Vec2 &v) const
{
	return this->x * v.x + this->y * v.y;
}

float Vec2::Cross(const Vec2 &v) const
{
	return this->x * v.y - this->y * v.x;
}

float Vec2::Magnitude() const
{
	return sqrt(x * x + y * y);
}

float Vec2::MagnitudeSquared() const
{
	return x * x + y * y;
}