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

private:
	float m_y;
	float m_x;
};

