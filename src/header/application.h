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
	bool isLeftButtonDown;
	float m_k;
	float m_restLenght;

	std::vector<Particle*> m_particles;

	Vec2 pushForces;
	Vec2 m_mouseCursor;
	Vec2 m_anchor;

	SDL_Rect liquid;
	Particle* selectedParticle;
};

