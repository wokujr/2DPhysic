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
	particle->m_radius = 15;
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

	particle->m_acceleration.SetX(2.0f * Constant::PIXELS_PER_METER);
	particle->m_acceleration.SetY(9.8f * Constant::PIXELS_PER_METER);

	//integrated acceleration and velocity to find new position
	particle->m_velocity += particle->m_acceleration * deltaTime;
	particle->m_position += particle->m_velocity * deltaTime;

	if (particle->m_position.GetX() - particle->m_radius <= 0)															// I have no idea what im doing
	{
		particle->m_position.SetX(particle->m_radius);
		
		float velocityX = particle->m_velocity.GetX();
		particle->m_velocity.SetX(velocityX * -1.0f);
	}
	else if (particle -> m_position.GetX() + particle->m_radius >= Graphics::Width())
	{
		particle->m_position.SetX(Graphics::Width() - particle->m_radius);

		float velocityX = particle->m_velocity.GetX();
		particle->m_velocity.SetX(velocityX * -1.0f);
	}

	if (particle->m_position.GetY() - particle->m_radius <= 0)
	{
		particle->m_position.SetY(particle->m_radius);

		float velocityY = particle->m_velocity.GetY();
		particle->m_velocity.SetY(velocityY * -1.0f);
	}
	else if (particle->m_position.GetY() + particle->m_radius >= Graphics::Height())
	{
		particle->m_position.SetY(Graphics::Height() - particle->m_radius);

		float velocityY = particle->m_velocity.GetY();
		particle->m_velocity.SetY(velocityY * -1.0f);
	}


}

void Application::Render()
{
	Graphics::ClearScreen(0xFF0526263);
	Graphics::DrawFillCircle(particle -> m_position.GetX(), particle->m_position.GetY(), particle->m_radius, 0xFFFFFFFF);
	Graphics::RenderFrame();
}

void Application::Destroy()
{
	delete particle;
	Graphics::CloseWindow();
}

