#pragma once

#include "SDL2/SDL.h"
#include "graphics.h"

class App {
	private:
		bool isRunning = false;
		Graphics graphics;
		Uint32 backgroundColor;
		Uint32 drawColow;

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