#include "force.h"


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
