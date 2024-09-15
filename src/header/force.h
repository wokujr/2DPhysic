#pragma once
#include "particles.h"
#include "vec2.h"


class Force
{
public:
	Force();
	~Force() = default;

	static Vec2 GenerateDragForce(const Particle& particle, float k);
};
