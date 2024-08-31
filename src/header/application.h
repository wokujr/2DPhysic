#pragma once

#include "graphics.h"
#include "particles.h"

class Application
{
public:
	Application();
	~Application() = default;

	bool isRunning();
	void Setup();
	void Input();
	void Update();
	void Render();
	void Destroy();

private:
	bool m_running;
	Particle* particle;
};

