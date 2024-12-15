#pragma once
#include <SDL_ttf.h>
#include "TextureManager.h"


enum class Fonts
{
	BOBBLE
};


class UIManager
{
private:
	UIManager();


	static UIManager* Instance;


	std::map<Fonts, TTF_Font*> fontList;


public:
	inline static UIManager* GetInstance() { return Instance = (Instance != nullptr) ? Instance : new UIManager(); }


	bool LoadFont(Fonts id, std::string textPath, int fontsize = 20);

	bool LoadText(texturesID id, Fonts font, std::string text, SDL_Color color, Uint32 wrapSize);
	
	void DrawText(texturesID id, SDL_Rect dest, Vector2 scale);

	void Clean();

	const std::map<Fonts, TTF_Font*>& GetFontList();
};