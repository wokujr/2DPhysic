#include "graphics.h"
#include <SDL2_gfxPrimitives.h>
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

/* Set the background col */
void Graphics::ClearScreen(Uint32 color)
{
	// Extract RGB components from the 24-bit color		// i made myself confuse with this, TeHe~. using the shifts bit position by 16 adn position by 8, so basically 0xRRGGBB.
	Uint8 red = (color >> 16) & 0xFF;					// Extract red component (bits 16-23)
	Uint8 green = (color >> 8) & 0xFF;					// Extract green component (bits 8-15)
	Uint8 blue = color & 0xFF;							// Extract blue component (bits 0-7)

	SDL_SetRenderDrawColor(renderer,  red,  green, blue, 255);
	SDL_RenderClear(renderer);
}

void Graphics::RenderFrame()
{
	SDL_RenderPresent(renderer);
}

void Graphics::DrawLine(int x0, int y0, int x1, int y1, Uint32 color)
{
	lineColor(renderer, x0, y0, x1, y1, color);
}

void Graphics::DrawCircle(int x, int y, int radius, float angle, Uint32 color)
{
	circleColor(renderer, x, y, radius, color);
	lineColor(renderer, x, y, x + cos(angle) * radius, y + sin(angle) * radius, color);
}

void Graphics::DrawFillCircle(int x, int y, int radius, Uint32 color)
{
	filledCircleColor(renderer, x, y, radius, color);
}

void Graphics::DrawRect(int x, int y, int width, int height, Uint32 color)
{
	boxColor(renderer, x - width / 2.0, y - height / 2.0, x + width / 2.0, y + height / 2.0, color);
}

void Graphics::DrawFillRect(int x, int y, int width, int height, Uint32 color)
{
	boxColor(renderer, x - width / 2.0, y - height / 2.0, x + width / 2.0, y + height / 2.0, color);
}

void Graphics::DrawPolygon(int x, int y, const std::vector<Vec2>& vertices, Uint32 color)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		int currentIndex = i;
		int nextIndex = (i + 1) % vertices.size();
		lineColor(renderer, vertices[currentIndex].GetX(), vertices[currentIndex].GetX(), vertices[nextIndex].GetX(), vertices[nextIndex].GetY(), color);	// IDK if this going to produce error
	}
	filledCircleColor(renderer, x, y, 1, color);
}

void Graphics::DrawFillPolygon(int x, int y, const std::vector<Vec2>& vertices, Uint32 color)
{
	std::vector<short> vectorX;
	std::vector<short>vectorY;
	for (int i = 0; i <vertices.size(); i++)
	{
		vectorX.push_back(static_cast<short>(vertices[i].GetX()));
		vectorY.push_back(static_cast<short>(vertices[i].GetY()));
	}
	filledPolygonColor(renderer, &vectorX[0], &vectorY[0], vertices.size(), color);
	filledCircleColor(renderer, x, y, 1, 0xFF000000);
}

void Graphics::DrawTexture(int x, int y, int width, int height, float rotation, SDL_Texture* texture)
{
	SDL_Rect dstRect = { x - (width / 2), y - (height / 2), width, height };
	float rotationDeg = rotation * 57.2958;
	SDL_RenderCopyEx(renderer, texture, nullptr, &dstRect, rotationDeg, nullptr, SDL_FLIP_NONE);
}

void Graphics::CloseWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}





