#pragma once
#include "particles.h"
#include "vec2.h"

class Force
{
public:
	Force();
	~Force() = default;


	/**
	 * 
	 * @param particle reference to particle
	 * @param k is just constant that made up value to make it more realistic?
	 */
	static Vec2 GenerateDragForce(const Particle& particle, float k);
	static Vec2 GenerateFrictionForce(const Particle& particle, float k);
	static Vec2 GenerateGravitionalForce(const Particle& particleA, const Particle& particleB, float G, float minDistance, float maxDistance);
	static Vec2 GenerateSpringForce(const Particle* particle, Vec2 anchor, float restLength, float k);

};