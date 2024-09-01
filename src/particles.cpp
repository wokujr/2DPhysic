#include "particles.h"

#include <iostream>

Particle::Particle(float x, float y, float mass)
	:
	position(Vec2(x, y)),
	mass(mass)
{
	std::cout << "Particle constructor called \n";
}

Particle::~Particle()
{
	std::cout << "Particle destruction \n";
}
