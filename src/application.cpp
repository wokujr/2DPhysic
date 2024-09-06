#include "application.h"

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
	/* Check if we are move too fast, and if so, waste some miliseconds, yes we move too fast we need to slow it down until it reach MILLISECS_PER_FRAME aka 1000/60 in this case */
	Constant constant;
	static int timePreviousFrame = 0; //should i make it static?
	int timeToWait = constant.MILLISECOND_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
	if (timeToWait > 0)
	{
		SDL_Delay(timeToWait);
	}
	timePreviousFrame = SDL_GetTicks();

	particle->m_velocity = Vec2(2.0, 0.0);

	//particle->m_position.Add(particle->m_velocity);
	particle->m_position += particle->m_velocity;

	/*float newX = particle->m_position.GetX() + particle->m_velocity.GetX();
	particle->m_position.SetX(newX);

	float newY = particle->m_position.GetY() + particle->m_velocity.GetX();
	particle->m_position.SetY(newY);*/
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

