#include "MessageHandler.h"

void MessageHandler::ShowMessageBox(messageType type)
{
	switch (type)
	{
	case messageType::INSTRUCTIONS:
		SDL_ShowMessageBox(&instructionMessage, NULL);
		break;
	case messageType::CONTROLLER_WARNING:
		SDL_ShowMessageBox(&controllerMessage, NULL);
		break;
	}
}
