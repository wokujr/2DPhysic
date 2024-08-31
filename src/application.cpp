#include "application.h"

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

}

void Application::Update()
{

}

void Application::Render()
{

}

void Application::Destroy()
{

}

