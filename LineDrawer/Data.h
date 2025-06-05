#pragma once
#include <raylib.h>
#include <math.h>

struct Vec2
{
	float x = 0.0f, y = 0.0f;

	Vec2() {}
	Vec2(float x, float y) : x(x), y(y) {}
	Vec2(Vector2 v) : x(v.x), y(v.y) {}

	inline float getLength() {
		return (float)sqrt(x * x + y * y);
	}

	inline bool operator==(const Vec2& rhs) const
	{ return x == rhs.x && y == rhs.y; }

	inline Vec2 operator+(const Vec2& rhs)
	{ return Vec2(x + rhs.x, y + rhs.y); }
	
	inline Vec2 operator-(const Vec2& rhs)
	{ return Vec2(x - rhs.x, y - rhs.y); }

	inline Vec2 operator*(float a)
	{ return Vec2(x * a, y * a); }

	void operator*=(float a)
	{ *this = *this * a; }

	void operator+=(const Vec2& rhs)
	{ *this = *this + rhs; }

	void operator-=(const Vec2& rhs)
	{ *this = *this - rhs; }

	inline operator Vector2()
	{ return Vector2{ x, y }; }
};

struct Line
{
	Vec2 start, end;

	bool touchingLine(Vec2 pos)
	{
		Vec2 startP(pos.x - start.x, pos.y - start.y);
		Vec2 endP(pos.x - end.x, pos.y - end.y);
		Vec2 lineV(start.x - end.x, start.y - end.y);

		return startP.getLength() + endP.getLength() - lineV.getLength() < 2.0f;
	}

	inline bool operator==(const Line& rhs) const
	{ return start == rhs.start && end == rhs.end; }
};
