#include "Application.h"


int main(int argc, char** argv)
{
	Application* App = new Application();

	App->Update();

	delete App;
	App = nullptr;

	return 0;
}