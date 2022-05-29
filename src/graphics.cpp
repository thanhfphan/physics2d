#include "graphics.h"

#include "log.h"

Graphics::Graphics() {}
Graphics::~Graphics() {}

void Graphics::OpenWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Log::Error(SDL_GetError());
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowHeight = displayMode.h;
	windowWidth = displayMode.w;
	window = SDL_CreateWindow("2D Physics Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
	if (!window)
	{
		Log::Error("cant init window");
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		Log::Error("cant init renderer");
	}
}

void Graphics::ClearScreen(const Uint32 color)
{
	Uint8 r = Uint8(color >> 16);
	Uint8 g = Uint8(color >> 8);
	Uint8 b = Uint8(color);
	SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
	SDL_RenderClear(renderer);
}

void Graphics::CloseWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Graphics::Render()
{
	SDL_RenderPresent(renderer);
}

int Graphics::Width()
{
	return windowWidth;
}

int Graphics::Height()
{
	return windowHeight;
}

void Graphics::DrawLine(float x1, float y1, float x2, float y2, Uint32 color)
{
	lineColor(renderer, x1, y1, x2, y2, color);
}

void Graphics::DrawCircle(float x, float y, int r, Uint32 color)
{
	circleColor(renderer, x, y, r, color);
	filledCircleColor(renderer, x, y, 1, color);
}

void Graphics::DrawFilledCircle(float x, float y, int r, Uint32 color)
{
	filledCircleColor(renderer, x, y, r, color);
}

void Graphics::DrawRectangle(int x1, int y1, int x2, int y2, Uint32 color)
{
	rectangleColor(renderer, x1, y1, x2, y2, color);
}

void Graphics::DrawPolygon(const std::vector<Vec2> &vertices, Uint32 color)
{
	int n = vertices.size();
	std::vector<Sint16> vx;
	std::vector<Sint16> vy;

	for (int i = 0; i < n; i++)
	{
		vx.push_back(vertices[i].x);
		vy.push_back(vertices[i].y);
	}

	polygonColor(renderer, &vx[0], &vy[0], n, color);
}