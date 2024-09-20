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
	 * @param k is coefficient which is how strong it's going to 
	 */
	static Vec2 GenerateDragForce(const Particle& particle, float k);
	static Vec2 GenerateFrictionForce(const Particle& particle, float k);
	static Vec2 GenerateGravitionalForce(const Particle& particleA, const Particle& particleB, float G, float minDistance, float maxDistance);
};