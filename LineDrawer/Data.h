#pragma once
#include <raylib.h>

struct Vec2
{
	float x, y;

	Vec2(Vector2 v) : x(v.x), y(v.y) {}

	bool operator==(const Vec2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
};

struct Line
{
	Vec2 start, end;

	inline bool operator==(const Line& rhs) const
	{
		return start == rhs.start && end == rhs.end;
	}
};
