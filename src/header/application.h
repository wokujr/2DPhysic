#pragma once
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

public:
	bool m_running;
	Particle* particle;

//private:
//	bool m_running;
//	Particle* particle;

};

