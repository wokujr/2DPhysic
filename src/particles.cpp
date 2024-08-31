#include "particles.h"

#include <iostream>

Particle::Particle()
{
}

Particle::Particle(float x, float y, float mass)
	:
	m_mass(mass),
	m_position( Vec2(x, y) )
{

	std::cout << "Particle constructor called \n";
}

Particle::~Particle()
{
	std::cout << "Particle destruction \n";
}
