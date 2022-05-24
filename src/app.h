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
	static const int FRAME_PER_SECOND = 60;
	static const int TIME_PER_FRAME = 1000 / FRAME_PER_SECOND;

public:
	std::vector<Body *> bodies;

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