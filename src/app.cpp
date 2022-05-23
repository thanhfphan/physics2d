#include <iostream>
#include "app.h"
#include "log.h"
#include "graphics.h"
#include "SDL2/SDL.h"
#include "shape.h"
#include "body.h"
#include "collision.h"

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
	drawColor = 0xFF00FF00;		  // xanh
	collisionColor = 0xFF0000FF;  // do

	Body *bCircle = new Body();
	bCircle->position = Vec2(600, 350);
	bCircle->shape = new Circle(150);
	bodies.push_back(bCircle);
}

void App::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
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
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	Body *bCircle = new Body();
	bCircle->position = Vec2(mouseX, mouseY);
	bCircle->shape = new Circle(50);

	for (Body *body : bodies)
	{
		if (body->shape->GetType() == "circle")
		{
			Circle *bC = (Circle *)body->shape;
			if (CircleToCircle(bCircle, body))
			{
				graphics.DrawCircle(body->position.x, body->position.y, bC->radius, collisionColor);
				graphics.DrawCircle(bCircle->position.x, bCircle->position.y, 50, collisionColor);
			}
			else
			{
				graphics.DrawCircle(body->position.x, body->position.y, bC->radius, drawColor);
				graphics.DrawCircle(bCircle->position.x, bCircle->position.y, 50, drawColor);
			}
		}
	}

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