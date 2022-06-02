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
	for (auto body : bodies){
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

	Box *box = new Box(400, 250);
	Body *b = new Body(box, 650, 400, 1);
	bodies.push_back(b);

	std::vector<Vec2> localVertices;
	localVertices.push_back(Vec2(-100, 300));
	localVertices.push_back(Vec2(-200, -500));
	localVertices.push_back(Vec2(300, 0));
	Polygon* polygon = new Polygon(localVertices);
	Body* p = new Body(polygon, 800,300, 1);
	bodies.push_back(p);

	Circle* circle = new Circle(200);
	Body *c = new Body(circle, 700, 600, 1);
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
		// Vec2 weightForce = Force::GenWeightForce(body, GRAVITY * METER_PER_PIXEL);
		// body->AddForce(weightForce);

		float torque = 40.0 * METER_PER_PIXEL; 
		body->AddTorque(torque);
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