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

	Circle *circle = new Circle(200);
	Body *c = new Body(circle, 600, 400, 0.0);
	bodies.push_back(c);
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
			Circle *circle = new Circle(40);
			Body *c = new Body(circle, positionMouseX, positionMouseY, 1);
			bodies.push_back(c);
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

		// float torque = 40.0 * METER_PER_PIXEL;
		// body->AddTorque(torque);
	}

	Contact contact;
	for (int i = 0; i < bodies.size(); i++)
	{
		for (int j = i +1; j < bodies.size(); j++)
		{
			if (Collision::IsColliding(bodies[i], bodies[j], contact))
			{
				contact.ResolveCollision();

				graphics.DrawFilledCircle(contact.start.x, contact.start.y, 3, collisionColor);
				graphics.DrawFilledCircle(contact.end.x, contact.end.y, 3, collisionColor);
				graphics.DrawLine(contact.start.x, contact.start.y, contact.start.x + contact.normal.x * 20, contact.start.y + contact.normal.y * 20, collisionColor);
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