#pragma once

#include "vec2.h"

class Particle
{
public:
	Particle(float x, float y, float mass);
	~Particle();

	Vec2 m_position;
	Vec2 m_velocity;
	Vec2 m_acceleration;

	float m_mass;
	
};