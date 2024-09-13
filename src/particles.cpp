#include "particles.h"

#include <iostream>

Particle::Particle(float x, float y, float mass)
{
	this->position = Vec2(x, y);
	this->mass = mass;
	std::cout << "Particle constructor called \n";
}

Particle::~Particle()
{
	std::cout << "Particle destruction called\n";
}

void Particle::Integrate(float deltaTime)
{
	//Find the acceleration based on the forces that being applied
	acceleration = sumForces / mass;

	//integrate acceleration to find new velocity
	velocity += acceleration * deltaTime;

	//integrate the velocity to find a new position (Euler Method)
	position += velocity * deltaTime;

	ClearForces();
}

void Particle::AddForce(const Vec2& force)
{
	sumForces += force;
}

void Particle::ClearForces()
{
	sumForces = Vec2(0.0f, 0.0f);
}

