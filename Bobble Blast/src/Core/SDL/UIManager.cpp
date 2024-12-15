#include "../../../include/Core/SDL/Renderer.h"
#include "../../../include/Debugging/Debug.h"
#include "../../../include/Math/Vector2.h"
#include "../../include/Core/SDL/UIManager.h"


UIManager* UIManager::Instance = nullptr;


UIManager::UIManager()
{
	if (TTF_Init() < 0)
	{
		std::cerr << "Failed to initialize SDL_ttf: " << SDL_GetError() << std::endl;
	}
};

bool UIManager::LoadFont(Fonts id, std::string textPath, int fontsize)
{
	fontList[id] = TTF_OpenFont(textPath.c_str(), fontsize);

#if _DEBUG
		DBG_ASSERT_MSG(fontList[id], "Failed to load the text: % s\n", TTF_GetError());
#endif

	return true;
}

bool UIManager::LoadText(texturesID id, Fonts font, std::string text, SDL_Color color, Uint32 wrapSize)
{
	if (wrapSize <= 0)
	{
		wrapSize = 1;
	}

	auto textSurface = TTF_RenderText_Blended_Wrapped(fontList[font], text.c_str(), color, wrapSize);

#if _DEBUG
	DBG_ASSERT_MSG(textSurface, "Failed to load the texture: % s\n", TTF_GetError());
#endif

	auto textTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetRenderer(), textSurface);

#if _DEBUG
	DBG_ASSERT_MSG(textTexture, "Failed to create the texture: % s\n", TTF_GetError());
#endif

	// Deleting temp surface
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;

	// TODO: This is horrible. Don't use the TextureManager to cache the text. USE SMART POINTERS!!!
	// Deleting previous texture
	SDL_DestroyTexture(TextureManager::GetInstance()->GetTextureMap().at(id));
	
	// Re-assign Updated text
	TextureManager::GetInstance()->SetTexture(id, textTexture);

	return true;
}

void UIManager::DrawText(texturesID id, SDL_Rect dest, Vector2 scale)
{
	SDL_Rect destRect = { dest.x, dest.y, dest.w * scale.x, dest.h * scale.y };

	SDL_RenderCopy(Renderer::GetInstance()->GetRenderer(), TextureManager::GetInstance()->GetTextureMap().at(id), NULL, &destRect);
}

void UIManager::Clean()
{
	for (auto it = fontList.begin(); it != fontList.end(); it++)
	{
		TTF_CloseFont(it->second);
	}

	fontList.clear();

#if _DEBUG
	DBG_ASSERT_MSG_EMPTY(fontList.size(), "DEBUG_MSG: FontList cleaned! \n");
#endif

	TTF_Quit();
}

const std::map<Fonts, TTF_Font*>& UIManager::GetFontList() 
{ 
	return fontList;
}