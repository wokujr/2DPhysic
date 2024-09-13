#pragma once

class Vec2
{
public:
	Vec2();
	Vec2(float x, float y);

	~Vec2() = default;

	void Add(const Vec2& vector);
	void Sub(const Vec2& vector);
	void Scale(const float number);
	Vec2 Rotate(const float angle) const;

	float Magnitude() const;
	float MagnitudeSquared() const;

	Vec2& Normalize();
	Vec2 UnitVector() const;
	Vec2 Normal() const;

	float Dot(const Vec2& vector) const;
	float Cross(const Vec2& vector) const;

	Vec2& operator = (const Vec2& vector);
	bool operator == (const Vec2& vector) const;
	bool operator != (const Vec2& vector) const;

	Vec2 operator + (const Vec2& vector) const;
	Vec2 operator - (const Vec2& vector) const;
	Vec2 operator * (const float number) const;
	Vec2 operator / (const float number) const;
	Vec2 operator - () const;

	Vec2 operator += (const Vec2& vector);
	Vec2 operator -= (const Vec2& vector);
	Vec2 operator *= (const float number);
	Vec2 operator /= (const float number);

	float GetX() const;
	float GetY() const;
	void SetX(float x);
	void SetY(float y);

private:
	float m_y;
	float m_x;
};



/*
 *  calculus is the theory where we need to find delta time aka elapsed time that needed to reach a certain position
 *	so the smaller the time, the more accurate and less error of estimation to reach a certain position, the idea is to find how we can reach value near 0, or less time,
 *	and be more accurate. that's why bigger FPS, make movement looks smoother, and precisely. especially in first person shooting game, where FPS(frame rate per second) is matter.
 *	there 2 calculus : differential calculus and integral calculus.
 */