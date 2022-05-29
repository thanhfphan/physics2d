#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "vec2.h"
#include "vector"

class Graphics
{
private:
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	int windowWidth = 0;
	int windowHeight = 0;

public:
	Graphics();
	~Graphics();
	void ClearScreen(const Uint32 color);
	void OpenWindow();
	void CloseWindow();
	void Render();
	int Width();
	int Height();

	void DrawLine(float x1, float y1, float x2, float y2, Uint32 color);
	void DrawCircle(float x, float y, int r, Uint32 color);
	void DrawFilledCircle(float x, float y, int r, Uint32 color);
	void DrawPolygon(const std::vector<Vec2> &vertices, Uint32 color);
	void DrawRectangle(int x1, int y1, int x2, int y2, Uint32 color);
};