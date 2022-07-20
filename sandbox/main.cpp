#include <iostream>
#include "app.h"

int main(int agrc, char** argv){

	App app;
	app.Setup();
	while (app.IsRunning())
	{
		app.ProcessInput();
		app.Update();
		app.Render();
	}

	app.Destroy();

	return 0;
}