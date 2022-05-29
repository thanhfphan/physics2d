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
	collisionColor = 0xFF0000FF; // do

	anchor = new Body(500, 150, 1);
	anchor->shape = new Circle(5);

	pushForce = Vec2();

	int height = 220;
	for (int i = 0; i < 15; i++)
	{
		Body *obj = new Body(500, height, 1);
		obj->shape = new Circle(7);
		bodies.push_back(obj);
		height += 20;
	}
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
		case SDL_MOUSEBUTTONUP:{
			pushForce = Vec2();
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			Vec2 mousePosition = Vec2(mouseX, mouseY);

			Body *lastBody = bodies[bodies.size() - 1];
			Vec2 d = (mousePosition - lastBody->position);
			Vec2 direction = d.UnitVector();

			pushForce = direction * 8;
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

	static float restLength = 15;
	static float k = 4;
	Body *firstBody = bodies[0];
	Vec2 springForce = Force::GenSpringForce(firstBody, anchor, restLength, k);
	firstBody->AddForce(springForce);

	for (auto body : bodies)
	{
		body->AddForce(pushForce);

		Vec2 weightForce = Force::GenWeightForce(body, GRAVITY);
		body->AddForce(weightForce);

		Vec2 dragForce = Force::GenDragForce(body, 0.000006);
		body->AddForce(dragForce);
	}

	for (int i = 1; i < bodies.size(); i++)
	{
		Body *prevBody = bodies[i - 1];
		Body *body = bodies[i];


		Vec2 springForce = Force::GenSpringForce(body, prevBody, restLength, k);
		body->AddForce(springForce);
		Vec2 springForce2 = -springForce;
		prevBody->AddForce(springForce2);
	}

	for (auto body : bodies)
	{
		body->Integrate(deltaTime);
	}

	for (auto body : bodies)
	{
		body->ClearForce();
	}
}

void App::Render()
{
	graphics.DrawFilledCircle(anchor->position.x, anchor->position.y, 5, 0xFF0000FF);

	for (int i = 0; i < bodies.size(); i++)
	{
		Body *body = bodies[i];
		if (body->shape->GetType() == "circle")
		{
			Circle *bC = (Circle *)body->shape;
			graphics.DrawFilledCircle(body->position.x, body->position.y, bC->radius, drawColor);
		}
		else if (body->shape->GetType() == "polygon")
		{
			Polygon *polygon = (Polygon *)body->shape;
			graphics.DrawPolygon(polygon->vertices, drawColor);
		}

		if (i == 0)
		{
			graphics.DrawLine(body->position.x, body->position.y, anchor->position.x, anchor->position.y, 0xFFFFFFFF);
		}
		else
		{
			Body *preBody = bodies[i - 1];
			graphics.DrawLine(body->position.x, body->position.y, preBody->position.x, preBody->position.y, 0xFFFFFFFF);
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