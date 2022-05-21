#include "app.h"
#include "log.h"
#include <iostream>
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

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Log::Error(SDL_GetError());
	}

	window = SDL_CreateWindow("Physics 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
	if (!window){
		Log::Error("cant init window");
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer){
		Log::Error("cant init renderer");
	}
}

void App::ProcessInput()
{
}

void App::Update()
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

void App::Render()
{
}

void App::Destroy()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool App::IsRunning()
{
	return isRunning;
}