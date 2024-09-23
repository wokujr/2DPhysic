#include "force.h"
#include <algorithm>


Force::Force()
{
}

/**
 * you know in real world when we move faster the drag force or maybe a resistant that push us backward, so this is implementation of drag force, not wind force but the energy that push us backward, it can be a liquid, water, etc.
 * @param particle 
 * @param k 
 * @return drag force
 */
Vec2 Force::GenerateDragForce(const Particle& particle, float k)
{
	Vec2 dragForce = Vec2(0.f, 0.f);
	if (particle.velocity.MagnitudeSquared() > 0)
	{
		//Calculate Drag Direction
		Vec2 dragDirection = particle.velocity.UnitVector() * -1.0f;

		//Calculate drag magnitude , aka k * |v|^2
		float dragMagnitude = k * particle.velocity.MagnitudeSquared();

		//Generate the final drag force
		dragForce = dragDirection * dragMagnitude;
	}

	return dragForce;
}

Vec2 Force::GenerateFrictionForce(const Particle& particle, float k)
{
	Vec2 frictionForce = Vec2(0.f, 0.f);

	Vec2 frictionDirection = particle.velocity.UnitVector() * -1.0f;	//Flip the velocity direction.

	float frictionMagnitude = k;

	frictionForce = frictionDirection * frictionMagnitude;
	return frictionDirection;
}

Vec2 Force::GenerateGravitionalForce(const Particle& particleA, const Particle& particleB, float G, float minDistance,
	float maxDistance)
{
	//Calculate distance between 2 particles
	Vec2 deltaDistance = (particleB.position - particleA.position);

	float distanceSquared = deltaDistance.MagnitudeSquared();

	//clamp the value
	distanceSquared = std::clamp(distanceSquared, minDistance, maxDistance);

	//Calculate the direction of the attraction
	Vec2 attractionDirection = deltaDistance.UnitVector();

	//Calculate the strength of attraction force
	float attractionMagnitude = G * (particleA.mass * particleB.mass) / distanceSquared;

	//calculate the final result
	Vec2 attractionForce = attractionDirection * attractionMagnitude;
	return attractionForce;
}

Vec2 Force::GenerateSpringForce(const Particle* particle, Vec2 anchor, float restLength, float k)
{
	//Calculate the distance between the anchor and the object(particle in this case);
	Vec2 delta = particle->position - anchor;

	//Find the spring displacement considering the rest length.
	float displacement = delta.Magnitude() - restLength;

	Vec2 springDirection = delta.UnitVector();
	float springMagnitude = -k * displacement;

	//Calculate the final force of spring force
	Vec2 springForce = springDirection * springMagnitude;
	return springForce;

}
