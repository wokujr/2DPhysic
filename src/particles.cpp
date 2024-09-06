#include "particles.h"

#include <iostream>

Particle::Particle(float x, float y, float mass)
	:
	m_position(Vec2(x, y)),
	m_mass(mass)
{
	this->m_position = Vec2(x, y);
	this->m_mass = mass;
	std::cout << "Particle constructor called \n";
}

Particle::~Particle()
{
	std::cout << "Particle destruction called\n";
}
