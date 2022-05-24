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

	Body *floor = new Body();
	std::vector<Vec2> floorVerticies;
	floorVerticies.push_back(Vec2(30, graphics.Height() - 150));
	floorVerticies.push_back(Vec2(30, graphics.Height() - 100));
	floorVerticies.push_back(Vec2(graphics.Width() - 30, graphics.Height() - 100));
	floorVerticies.push_back(Vec2(graphics.Width() - 30, graphics.Height() - 150));
	floor->shape = new Polygon(floorVerticies);
	bodies.push_back(floor);
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
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				isRunning = false;
			}
			break;
		case SDL_MOUSEBUTTONUP:
		{
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			Body *bCircle = new Body();
			bCircle->position = Vec2(mouseX, mouseY);
			bCircle->shape = new Circle(50);
			bCircle->acceleration= Vec2(0, 9.8);
			bodies.push_back(bCircle);
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

	static int timeInPreviousFrame;
	int timeToWait = TIME_PER_FRAME - (SDL_GetTicks() - timeInPreviousFrame);
	if (timeToWait > 0)
	{
		SDL_Delay(timeToWait);
	}
	float deltaTime = (SDL_GetTicks() - timeInPreviousFrame) / 1000.0;
	if (deltaTime > 0.016)
	{
		deltaTime = 0.016;
	}
	timeInPreviousFrame = SDL_GetTicks();

	for (Body *body : bodies)
	{
		body->Movement(deltaTime);
	}

	// show in screen
	for (Body *body : bodies)
	{
		if (body->shape->GetType() == "circle")
		{
			Circle *bC = (Circle *)body->shape;
			if (body->position.y + bC->radius + 150 > graphics.Height())
			{
				body->position.y = graphics.Height() - 150 - bC->radius;
			}
		}
	}
}

void App::Render()
{
	for (int i = 0; i < bodies.size(); i++)
	{
		Body *body = bodies[i];
		if (body->shape->GetType() == "circle")
		{
			Circle *bC = (Circle *)body->shape;
			graphics.DrawCircle(body->position.x, body->position.y, bC->radius, drawColor);
		}
		else if (body->shape->GetType() == "polygon")
		{
			Polygon *polygon = (Polygon *)body->shape;
			graphics.DrawPolygon(polygon->vertices, drawColor);
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