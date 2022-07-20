#include <iostream>
#include "app.h"
#include "graphics.h"
#include "SDL2/SDL.h"
#include "../src/collision.h"
#include "../src/const.h"
#include "../src/TK/Log.h"

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
	world = new World(GRAVITY);
	isRunning = true;
	graphics.OpenWindow();
	backgroundColor = 0xFF0F0721;
	drawColor = 0xFF00FF00;
	collisionColor = 0xFF0000FF;
	pushForce = Vec2();

	std::vector<Vec2> vericesFloor = {Vec2(-700, 25), Vec2(-700, -25), Vec2(700, -25), Vec2(700, 25)};
	Polygon *polygonFloor = new Polygon(vericesFloor);
	Body *floor = new Body(polygonFloor, graphics.Width() / 2, graphics.Height() - 200, 0);
	floor->restitution = 0.2f;
	world->CreateBody(floor);

	std::vector<Vec2> verices = {Vec2(-100, 100), Vec2(-100, -100), Vec2(100, -100), Vec2(100, 100)};
	Polygon *polygon = new Polygon(verices);
	Body *b = new Body(polygon, graphics.Width() / 2, graphics.Height() / 2 - 100, 0);
	b->rotation = 0.4;
	b->restitution = 0.5f;
	world->CreateBody(b);

	Log::Info("App:Setup had called ...");
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
			// std::vector<Vec2> vericesBox = {Vec2(-20, 20), Vec2(-20, -20), Vec2(20, -20), Vec2(20, 20)};
			// Polygon *sbox = new Polygon(vericesBox);
			// Body *box = new Body(sbox, mouseX, mouseY, 1);
			// bodies.push_back(box);
			Circle *c = new Circle(30);
			Body *b = new Body(c, mouseX, mouseY, 1);
			world->CreateBody(b);
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			break;
		}
		case SDL_MOUSEMOTION:
		{
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

	world->Step(deltaTime);

	std::vector<Body *> bodies = world->GetBodies();
	for (size_t i = 0; i < bodies.size() - 1; i++)
	{
		for (size_t j = i + 1; j < bodies.size(); j++)
		{
			Contact contact;
			Body *a = bodies[i];
			Body *b = bodies[j];
			if (Collision::IsColliding(a, b, contact))
			{
				contact.ResolveCollision();
				graphics.DrawFilledCircle(contact.start.x, contact.start.y, 5, collisionColor);
				graphics.DrawFilledCircle(contact.end.x, contact.end.y, 5, collisionColor);
				graphics.DrawLine(contact.start.x, contact.start.y, contact.start.x + contact.normal.x * 15, contact.start.y + contact.normal.y * 15, 0xFFFF00FF);
			}
		}
	}
}

void App::Render()
{
	for (auto body : world->GetBodies())
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