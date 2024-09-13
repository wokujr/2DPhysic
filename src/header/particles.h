#pragma once

#include "vec2.h"

class Particle
{
public:
	Particle(float x, float y, float mass);
	~Particle();

	void Integrate(float deltaTime);
	void AddForce(const Vec2& force);
	void ClearForces();

	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;
	Vec2 sumForces;

	float mass;
	float radius;
};