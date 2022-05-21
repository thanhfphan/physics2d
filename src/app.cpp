#include <iostream>
#include "app.h"
#include "log.h"
#include "graphics.h"
#include "SDL2/SDL.h"

App::App()
{
	Log::Info("App constructor had called");
}

App::~App()
{
	Log::Info("App destructor had called");
}

void App::Setup()
{
	std::cout << "App:Setup had called ..." << std::endl;
	isRunning = true;
	graphics.OpenWindow();
	backgroundColor = 0xFF0F0721; // tim
	drawColow = 0xFF00FF00; // xanh
}

void App::ProcessInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				isRunning = false;
				break;
			
			default:
				break;
			}
		default:
			break;
		}
	}
}

void App::Update()
{
	graphics.ClearScreen(backgroundColor);
}

void App::Render()
{
	graphics.DrawLine(100, 100, 300, 500, drawColow);
	graphics.DrawCircle(500, 500, 100, drawColow);

	std::vector<Vec2> vertices;
	vertices.push_back(Vec2(200, 200));
	vertices.push_back(Vec2(210, 410));
	vertices.push_back(Vec2(420, 430));
	vertices.push_back(Vec2(400, 200));
	graphics.DrawPolygon(vertices, drawColow);

	graphics.Render();
}

void App::Destroy()
{
	graphics.CloseWindow();
}

bool App::IsRunning()
{
	return isRunning;
}