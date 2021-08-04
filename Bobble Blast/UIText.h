#pragma once
#include "UIManager.h"


class UIText
{
private:
	texturesID textID;
	Fonts font;

	std::string Text;
	SDL_Color color;
	SDL_Rect textRect;

public:
	UIText(texturesID p_id, Fonts p_font, std::string p_text);
	~UIText();

	void Update(Uint32 wrapSize);
	void Draw(Vector2D p_scale, bool center = false, SDL_RendererFlip p_flip = SDL_FLIP_NONE);

	//Setters
	void ChangeColor(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);
	void SetPos(int p_x, int p_y);
	void SetWidthAndHeight(int p_w, int p_h);
	void SetWidthAndHeightByText();
	void SetText(std::string newText);

	//Getters
	inline SDL_Rect GetTextureDim() { return textRect; }

	//For debug
	inline void DrawTextBox(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		SDL_SetRenderDrawColor(Renderer::GetInstance()->GetRenderer(), r, g, b, a);
		SDL_RenderDrawRect(Renderer::GetInstance()->GetRenderer(), &textRect);
	}
};