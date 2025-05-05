#pragma once
#include <raylib.h>
#include <math.h>

struct Vec2
{
	float x = 0.0f, y = 0.0f;

	Vec2() {}
	Vec2(float x, float y) : x(x), y(y) {}
	Vec2(Vector2 v) : x(v.x), y(v.y) {}

	inline float getLength()
	{
		return sqrt(x * x + y * y);
	}

	inline bool operator==(const Vec2& rhs) const
	{ return x == rhs.x && y == rhs.y; }

	inline operator Vector2()
	{ return Vector2{ x, y }; }
};

struct Line
{
	Vec2 start, end;

	inline bool operator==(const Line& rhs) const
	{ return start == rhs.start && end == rhs.end; }
};
