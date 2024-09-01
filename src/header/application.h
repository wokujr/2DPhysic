#pragma once
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
	static void Render();
	void Destroy();

private:
	bool m_running;
	Particle* particle;
};

