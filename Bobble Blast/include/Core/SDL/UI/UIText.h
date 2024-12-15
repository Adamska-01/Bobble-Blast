#pragma once
#include <string>
#include "../TextureManager.h"
#include "../UIManager.h"


class UIText
{
private:
	texturesID textID;
	
	Fonts font;

	std::string Text;
	
	SDL_Color color;
	
	SDL_Rect textRect;


public:
	UIText(texturesID id, Fonts font, std::string text);
	
	~UIText() = default;


	void Update(Uint32 wrapSize);

	void Draw(Vector2 scale, bool center = false);

	void ChangeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	
	void SetPos(int x, int y);
	
	void SetWidthAndHeight(int w, int h);
	
	void SetWidthAndHeightByText();
	
	void SetText(std::string newText);

	SDL_Rect GetTextureDim();

	void DrawTextBox(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Rect textRect);
};