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
	for (auto body : bodies)
	{
		delete body;
	}
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

	std::vector<Vec2> verices = {Vec2(-100, 100), Vec2(-100, -100), Vec2(100, -100), Vec2(100, 100)};
	Polygon *polygon = new Polygon(verices);
	Body *b = new Body(polygon, 720, 400, 0);
	b->rotation = 0.4;
	bodies.push_back(b);

	std::vector<Vec2> vericesFloor = {Vec2(-700, 25), Vec2(-700, -25), Vec2(700, -25), Vec2(700, 25)};
	Polygon *polygonFloor = new Polygon(vericesFloor);
	Body *floor = new Body(polygonFloor, 720, 700, 0);
	floor->restitution = 0.2f;
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
			std::vector<Vec2> vericesBox= {Vec2(-20, 20), Vec2(-20, -20), Vec2(20, -20), Vec2(20, 20)};
			Polygon *sbox = new Polygon(vericesBox);
			Body *box = new Body(sbox, mouseX, mouseY, 1);
			bodies.push_back(box);
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

	// Time per frame
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
	// End - Time per frame

	for (auto body : bodies)
	{
		Vec2 weightForce = Force::GenWeightForce(body, GRAVITY * METER_PER_PIXEL);
		body->AddForce(weightForce);

		// float torque = 10.0 * METER_PER_PIXEL;
		// body->AddTorque(torque);
	}

	for (int i = 0; i < bodies.size(); i++)
	{
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Contact contact;
			Body *a = bodies[i];
			Body *b = bodies[j];
			if (Collision::IsColliding(a, b, contact))
			{
				contact.ResolveCollision();
			}
		}
	}
	for (auto body : bodies)
	{
		body->Update(deltaTime);
	}
}

void App::Render()
{
	for (auto body : bodies)
	{
		graphics.DrawBody(body, drawColor);
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