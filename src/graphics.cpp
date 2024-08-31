#include "graphics.h"
#include <iostream>

int Graphics::m_windowWidth = 0;
int Graphics::m_windowHeight = 0;
SDL_Window* Graphics::window = nullptr;
SDL_Renderer* Graphics::renderer = nullptr;

Graphics::Graphics()
{

}

int Graphics::Width()
{
	return m_windowWidth;
}

int Graphics::Height()
{
	return m_windowHeight;
}

bool Graphics::OpenWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL \n";
		return false;
	}
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	m_windowWidth = display_mode.w;
	m_windowHeight = display_mode.h;
	window = SDL_CreateWindow(nullptr, 0, 0, m_windowWidth, m_windowHeight, SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		std::cerr << "Error initializing SDL (display_mode) \n";
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		std::cerr << "Error initializing SDL (renderer)";
		return false;
	}
	return true;
}

void Graphics::ClearScreen(Uint32 color)
{
	SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
	SDL_RenderClear(renderer);
}

void Graphics::DrawLine(int x0, int y0, int x1, int y1, Uint32 color)
{
	
}


