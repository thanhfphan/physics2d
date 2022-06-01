#include <iostream>
#include "app.h"
#include "log.h"
#include "graphics.h"
#include "SDL2/SDL.h"
#include "shape.h"
#include "body.h"
#include "collision.h"
#include "const.h"
#include "force.h"

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
	backgroundColor = 0xFF0F0721;
	drawColor = 0xFF00FF00;
	collisionColor = 0xFF0000FF;
	pushForce = Vec2();

	// custom
	positionMouseX = 0;
	positionMouseY = 0;

	Body *staticBody = new Body(500, 500, 1);
	std::vector<Vec2> vertices = {Vec2(0, 200), Vec2(-200, 0), Vec2(200, 0)};
	Polygon *triangle = new Polygon(vertices);
	staticBody->shape = triangle;
	bodies.push_back(staticBody);
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
			pushForce = Vec2();
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			break;
		}
		case SDL_MOUSEMOTION:
		{
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			positionMouseX = mouseX;
			positionMouseY = mouseY;

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

	for (auto body : bodies)
	{
		body->Integrate(deltaTime);
		if (body->shape->GetType() == "polygon")
		{
			Polygon *polygon = (Polygon *)body->shape;
			polygon->UpdateVertices(body->position);
		}
	}

	for (auto body : bodies)
	{
		body->ClearForce();
	}
}

void App::Render()
{
	Body *tBody = new Body(positionMouseX, positionMouseY, 1);
	std::vector<Vec2> veticles = {Vec2(500, 0), Vec2(500, 300), Vec2(100,100)};
	Polygon *po = new Polygon(veticles);
	tBody->shape = po;
	po->UpdateVertices(tBody->position);

	Uint32 color = drawColor;

	for (auto body : bodies)
	{
		if (Collision::PolygonToPylygon(body, tBody))
		{
			color = collisionColor;
		}
		graphics.DrawBody(body, color);
	}

	graphics.DrawBody(tBody, color);

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