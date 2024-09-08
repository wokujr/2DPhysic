#include "application.h"

#include <iostream>
#include <windows.h>
#include "graphics.h"
#include "constants.h"

Application::Application()
	:
	m_running(false),
	particle(nullptr)
{
}

bool Application::IsRunning()
{
	return m_running;
}

void Application::Setup()
{
	m_running = Graphics::OpenWindow();
	particle = new Particle(50, 100, 1.0);
}

void Application::Input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym = SDLK_ESCAPE)
			{
				m_running = false;
			}
			break;
		}
	}
}

/*Called several times per second, meaning called per FPS */
void Application::Update()
{
	static int timePreviousFrame = 0;						
	static int frameCount = 0;
	static float fps = 0.0;
	static int timeAccumulator = 0;

	int currentTime = SDL_GetTicks();
	float elapsedTime = currentTime - timePreviousFrame;

	//Update timePreviousTime
	timePreviousFrame = currentTime;

	// Accumulated time for FPS calculation (after every second)
	timeAccumulator += elapsedTime;
	frameCount++;

	if (timeAccumulator >= 1000)
	{
		fps = frameCount / (timeAccumulator / 1000.0f);
		std::cout << "Current FPS= " << fps << "\n";

		//Reset Frame count for next second
		frameCount = 0;
		timeAccumulator = 0;
	}

	/* Check if we are move too fast, and if so, waste some milliseconds, yes we move too fast we need to slow it down until it reach MILLISECS_PER_FRAME aka 1000/60 in this case */
	int timeToWait = Constant::MILLISECOND_PER_FRAME - (currentTime - timePreviousFrame);
	if (timeToWait > 0)
	{
		SDL_Delay(timeToWait);
	}
	float deltaTime = elapsedTime / 1000.f;
	if (deltaTime > Constant::maxDeltaTime)
	{
		deltaTime = Constant::maxDeltaTime;
	}

	particle->m_velocity = Vec2(100.0 * deltaTime, 30.0 * deltaTime);

	//particle->m_position.Add(particle->m_velocity);
	particle->m_position += particle->m_velocity;
}

void Application::Render()
{
	Graphics::ClearScreen(0xFF0526263);
	Graphics::DrawFillCircle(particle -> m_position.GetX(), particle->m_position.GetY(), 20, 0xFFFFFFFF);
	Graphics::RenderFrame();
}

void Application::Destroy()
{
	delete particle;
	Graphics::CloseWindow();
}

