#pragma once

#include "vec2.h"

class Particle
{
public:
	Particle(float x, float y, float mass);
	~Particle();

	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;

	float mass;
	
};