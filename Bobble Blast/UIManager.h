#pragma once
#include <SDL_ttf.h>
#include "TextureManager.h"
#include "Debug.h"


enum class Fonts
{
	BOBBLE
};


class UIManager
{
private:
	UIManager() {
		//init ttf
		if (TTF_Init() < 0)
			std::cout << "Error: " << TTF_GetError() << std::endl;
	};
	static UIManager* Instance;

	std::map<Fonts, TTF_Font*> FontList;

public:
	inline static UIManager* GetInstance() { return Instance = (Instance != nullptr) ? Instance : new UIManager(); }

	bool LoadFonts(Fonts p_id, std::string p_textPath, int p_fontsize = 20);

	bool LoadText(texturesID p_id, Fonts p_font, std::string p_text, SDL_Color p_color, Uint32 p_wrapsize);
	
	void DrawText(texturesID p_id, SDL_Rect p_dst, Vector2D p_scale, SDL_RendererFlip p_flip = SDL_FLIP_NONE);

	void Clean();

	//Getter
	inline std::map<Fonts, TTF_Font*> GetFontList() { return FontList; }
};