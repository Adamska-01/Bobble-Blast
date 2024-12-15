#include "../../../../include/Core/SDL/MessageBox/MessageHandler.h"
#include "../../../../include/Core/SDL/MessageBox/MessageBoxConfig.h"


int MessageHandler::ShowMessageBox(const MessageBoxConfig& config)
{
	auto& buttons = config.buttons;

	SDL_MessageBoxData messageBoxData = {
		config.type,
		nullptr,
		config.title.c_str(),
		config.message.c_str(),
		buttons.size(),
		buttons.empty() ? nullptr : buttons.data(),
		nullptr 
	};

	auto buttonId = -1;
	
	if (SDL_ShowMessageBox(&messageBoxData, &buttonId) < 0) 
	{
		SDL_Log("Error displaying message box: %s", SDL_GetError());
	}

	return buttonId;
}