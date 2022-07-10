#pragma once

#include "SDL2/SDL.h"
#include "graphics.h"
#include "body.h"

class App
{
private:
	bool isRunning = false;
	Graphics graphics;
	Uint32 backgroundColor;
	Uint32 drawColor;
	Uint32 collisionColor;
	std::vector<Body *> bodies;
	Vec2 pushForce;

public:
	App();
	~App();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
	bool IsRunning();
};