#pragma once
#include "SDL2/SDL.h"

class App {
	private:
		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
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