#include "application.h"

#include <iostream>
#include <windows.h>
#include "graphics.h"
#include "constants.h"

Application::Application()
	:
	m_running(false)
{
}

bool Application::IsRunning()
{
	return m_running;
}

void Application::Setup()
{
	m_running = Graphics::OpenWindow();

	Particle* smallBall = new Particle(50, 100, 1.0);			//smallBall.... LMAO
	smallBall->radius = 6;
	m_particles.push_back(smallBall);

	Particle* bigBall = new Particle(50, 200, 3.0);			
	bigBall->radius = 12;
	m_particles.push_back(bigBall);
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
	static float timePreviousFrame = 0.f;						
	static int frameCount = 0;
	static float fps = 0.0;
	static float timeAccumulator = 0.f;

	UINT64 currentTime = SDL_GetTicks64();
	float elapsedTime = static_cast<float>(currentTime) - timePreviousFrame;

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

	for (auto particle: m_particles)
	{
		//Add "wind" force
		Vec2 wind = Vec2(1.f * Constant::PIXELS_PER_METER, 0.0f );
		particle->AddForce(wind);

		//Add "Weight" force to particle
		Vec2 weight = Vec2(0.f, 9.8f * Constant::PIXELS_PER_METER);
		particle->AddForce(weight);

		//integrate velocity to estimate new position
		particle->Integrate(deltaTime);

		if (particle->position.GetX() - particle->radius <= 0)
		{
			particle->position.SetX(particle->radius);
			
			float velocityX = particle->velocity.GetX();
			particle->velocity.SetX(velocityX * -1.0f);
		}
		else if (particle-> position.GetX() + particle->radius >= Graphics::Width())
		{
			particle->position.SetX(Graphics::Width() - particle->radius);

			float velocityX = particle->velocity.GetX();
			particle->velocity.SetX(velocityX * -1.0f);
		}

		if (particle->position.GetY() - particle->radius <= 0)
		{
			particle->position.SetY(particle->radius);

			float velocityY = particle->velocity.GetY();
			particle->velocity.SetY(velocityY * -1.0f);
		}
		else if (particle->position.GetY() + particle->radius >= Graphics::Height())
		{
			particle->position.SetY(Graphics::Height() - particle->radius);

			float velocityY = particle->velocity.GetY();
			particle->velocity.SetY(velocityY * -1.0f);
		}
	}
}

void Application::Render()
{
	Graphics::ClearScreen(0x13746B);			//change the background color, but it's kinda complicated
	for (auto particle: m_particles)
	{
		Graphics::DrawFillCircle(particle-> position.GetX(), particle->position.GetY(), particle->radius, 0xFFFFFFFF);
	}
	Graphics::RenderFrame();
}

void Application::Destroy()
{
	for (auto particle: m_particles)
	{
		delete particle;
	}
	Graphics::CloseWindow();
}

