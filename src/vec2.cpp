#include "vec2.h"
#include <cmath>

Vec2::Vec2()
	:
	m_x(0.0),
	m_y(0.0)
{
	
}

Vec2::Vec2(float x, float y)
	:
	m_x(x),
	m_y(y)
{
	
}

void Vec2::Add(const Vec2& vector)
{
	m_x += vector.m_x;
	m_y += vector.m_y;
}

void Vec2::Sub(const Vec2& vector)
{
	m_x -= vector.m_x;
	m_y -= vector.m_y;
}

void Vec2::Scale(const float number)
{
	m_x += number;
	m_y += number;
}

Vec2 Vec2::Rotate(const float angle) const
{
	Vec2 result;
	result.m_x = m_x * cos(angle) - m_y * sin(angle);
	result.m_y = m_x * sin(angle) + m_y * cos(angle);
	return result;
}

float Vec2::Magnitude() const {
	return sqrtf(m_x * m_x + m_y * m_y);
}

float Vec2::MagnitudeSquared() const {
	return (m_x * m_x + m_y * m_y);
}

Vec2& Vec2::Normalize() {
	float length = Magnitude();
	if (length != 0.0) {
		m_x /= length;
		m_y /= length;
	}
	return *this;
}

Vec2 Vec2::UnitVector() const {
	Vec2 result = Vec2(0, 0);
	float length = Magnitude();
	if (length != 0.0) {
		result.m_x = m_x / length;
		result.m_y = m_y / length;
	}
	return result;
}

Vec2 Vec2::Normal() const {
	return Vec2(m_y, -m_x).Normalize();
}

float Vec2::Dot(const Vec2& vector) const {
	return (m_x * vector.m_x) + (m_y * vector.m_y);
}

float Vec2::Cross(const Vec2& vector) const {
	return (m_x * vector.m_y) - (m_y * vector.m_x);
}

Vec2& Vec2::operator = (const Vec2& vector) {
	m_x = vector.m_x;
	m_y = vector.m_y;
	return *this;
}

bool Vec2::operator == (const Vec2& vector) const {
	return m_x == vector.m_x && m_y == vector.m_y;
}

bool Vec2::operator != (const Vec2& vector) const {
	return !(*this == vector);
}

Vec2 Vec2::operator + (const Vec2& vector) const
{
	Vec2 result;
	result.m_x = m_x + vector.m_x;
	result.m_y = m_y + vector.m_y;
	return result;
}

Vec2 Vec2::operator - (const Vec2& vector) const
{
	Vec2 result;
	result.m_x = m_x - vector.m_x;
	result.m_y = m_y - vector.m_y;
	return result;
}

Vec2 Vec2::operator * (const float number) const
{
	Vec2 result;
	result.m_x = m_x * number;
	result.m_y = m_y * number;
	return result;
}

Vec2 Vec2::operator / (const float number) const
{
	Vec2 result;
	result.m_x = m_x / number;
	result.m_y = m_y / number;
	return result;
}

Vec2 Vec2::operator - () const
{
	Vec2 result;
	result.m_x = m_x * -1;
	result.m_y = m_y * -1;
	return result;
}

Vec2 Vec2::operator += (const Vec2& vector)
{
	m_x += vector.m_x;
	m_y += vector.m_y;
	return *this;
}

Vec2 Vec2::operator -= (const Vec2& vector)
{
	m_x -= vector.m_x;
	m_y -= vector.m_y;
	return *this;
}

Vec2 Vec2::operator *= (const float number)
{
	m_x *= number;
	m_y *= number;
	return *this;
}

Vec2 Vec2::operator /= (const float number)
{
	m_x /= number;
	m_y /= number;
	return *this;
}

float Vec2::GetX() const
{
	return m_x;
}

float Vec2::GetY() const
{
	return m_y;

}

void Vec2::SetX(float x)
{
	m_x = x;
}

void Vec2::SetY(float y)
{
	m_y = y;
}


