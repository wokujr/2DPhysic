#pragma once

#include <SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include<SDL2_gfxPrimitives.h>
#include <vector>
#include "vec2.h"

class Graphics
{
public:
	Graphics();
	~Graphics() = default;

	static int Width();
	static int Height();
	static bool OpenWindow();
	static void CloseWindow();
	static void ClearScreen(Uint32 color);
	static void RenderFrame();
	static void DrawLine(int x0, int y0, int x1, int y1, Uint32 color);
	static void DrawCircle(int x, int y, int radius, float angle, Uint32 color);
	static void DrawFillCircle(int x, int y, int radius, Uint32 color);
	static void DrawRect(int x, int y, int width, int height, Uint32 color);
	static void DrawFillRect(int x, int y, int width, int height, Uint32 color);
	static void DrawPolygon(int x, int y, const std::vector<Vec2>& vertices, Uint32 color);
	static void DrawFillPolygon(int x, int y, const std::vector<Vec2>& vertices, Uint32 color);
	static void DrawTexture(int x, int y, int width, int height, float rotation, SDL_Texture* texture);

private:
	static int m_windowWidth;
	static int m_windowHeight;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
};