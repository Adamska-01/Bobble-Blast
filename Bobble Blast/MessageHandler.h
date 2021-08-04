#pragma once
#include <SDL.h>

enum class messageType
{
	INSTRUCTIONS, 
	CONTROLLER_WARNING
};

class MessageHandler
{
private:
	const SDL_MessageBoxButtonData button = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" };
	const SDL_MessageBoxData controllerMessage = { SDL_MESSAGEBOX_ERROR, 
		NULL, 
		"Controller Error",
		"Controller not detected !!! - \nInsert controller and press Escape",
		0,
		NULL,
		NULL};
	const SDL_MessageBoxData instructionMessage = { SDL_MESSAGEBOX_ERROR,
		NULL,
		"Controller instructions",
		"Shoot the falling bobbles before they reach the ground! (MATCH THE COLOUR!!!) \n\nA = Shoot \n<- and -> = rotate cannon \nLB and RB = Change bobble colour\n\nPress Escape to close this box",
		0,
		NULL,
		NULL };

public:
	MessageHandler() {}
	~MessageHandler() {};

	void ShowMessageBox(messageType type);
};