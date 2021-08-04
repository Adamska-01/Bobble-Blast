#include "UIText.h"

UIText::UIText(texturesID p_id, Fonts p_font, std::string p_text)
	:textID(p_id), font(p_font), Text(p_text)
{
}

UIText::~UIText()
{
}

void UIText::Update(Uint32 wrapSize)
{
	UIManager::GetInstance()->LoadText(textID, font, Text, color, wrapSize);
}

void UIText::Draw(Vector2D p_scale, bool center, SDL_RendererFlip p_flip)
{
	if (center)
	{
		SDL_Rect dest{ textRect.x - (textRect.w / 2), textRect.y - (textRect.h / 2), textRect.w, textRect.h };
		UIManager::GetInstance()->DrawText(textID, dest, p_scale, p_flip);

#if _DEBUG
		SDL_SetRenderDrawColor(Renderer::GetInstance()->GetRenderer(), 50, 80, 255, 255);
		SDL_RenderDrawRect(Renderer::GetInstance()->GetRenderer(), &dest);
#endif
	}
	else
	{
#if _DEBUG
		DrawTextBox(50, 80, 255, 255);
#endif
		UIManager::GetInstance()->DrawText(textID, textRect, p_scale, p_flip);
	}
}

void UIText::ChangeColor(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	color.r = p_r;
	color.g = p_g;
	color.b = p_b;
	color.a = p_a;
}

void UIText::SetPos(int p_x, int p_y)
{
	textRect.x = p_x;
	textRect.y = p_y;
}

void UIText::SetWidthAndHeight(int p_w, int p_h)
{
	textRect.w = p_w;
	textRect.h = p_h;
}

void UIText::SetWidthAndHeightByText()
{
	SDL_QueryTexture(TextureManager::GetInstance()->GetTextureMap()[textID], NULL, NULL, &textRect.w, &textRect.h);
}

void UIText::SetText(std::string newText)
{
	Text = newText;
}
