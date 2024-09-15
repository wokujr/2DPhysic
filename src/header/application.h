#pragma once
#include <SDL_rect.h>
#include <vector>

#include "particles.h"

class Application
{
public:
	Application();
	~Application() = default;

	bool IsRunning();
	void Setup();
	void Input();
	void Update();
	void Render();
	void Destroy();

private:
	bool m_running;
	std::vector<Particle*> m_particles;
	Vec2 pushForces;

	SDL_Rect liquid;
};

