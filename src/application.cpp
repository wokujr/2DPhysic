#include "application.h"

#include <windows.h>
#include "graphics.h"

Application::Application()
	:
	m_running(false)
{

}

bool Application::isRunning()
{
	return m_running;
}

void Application::Setup()
{
	m_running = Graphics::OpenWindow();
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

void Application::Update()
{

}

void Application::Render()
{
	Graphics::ClearScreen(0xFF0526263);
	Graphics::DrawFillCircle(200, 200, 40, 0xFFFFFFFF);
	Graphics::RenderFrame();
}

void Application::Destroy()
{
	Graphics::CloseWindow();
}

