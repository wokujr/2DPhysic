#pragma once

#include "vec2.h"

class Particle
{
public:
	Particle();
	Particle(float x, float y, float mass);

	~Particle();

	

private:
	float m_mass;
	Vec2 m_position;
	Vec2 m_velocity;
	Vec2 m_acceleration;


};