#pragma once

#include "SDL2/SDL.h"
#include "graphics.h"
#include "world.h"

class App
{
private:
	bool isRunning = false;
	Graphics graphics;
	Uint32 backgroundColor;
	Uint32 drawColor;
	Uint32 collisionColor;
	Vec2 pushForce;
	World *world;

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