#pragma once

struct Vec2
{
	float x, y;
	Vec2();
	Vec2(float x, float y);

	Vec2 operator+(const Vec2 &v) const;
	Vec2 operator-(const Vec2 &v) const;
	Vec2 operator*(const float n) const;
	Vec2 operator/(const float n) const;

	Vec2 operator-() const;

	Vec2& operator+=(const Vec2 &v);
	Vec2& operator-=(const Vec2 &v);
	Vec2& operator*=(const float n);
	Vec2& operator/=(const float n);

	Vec2 Rotate(const float angle) const;
	Vec2 &Normalise();
	Vec2 UnitVector() const;
	Vec2 Normal() const;

	void Scale(const float n);

	float Dot(const Vec2 &v) const;
	float Cross(const Vec2 &v) const;
	float Magnitude() const;
	float MagnitudeSquared() const;
};
