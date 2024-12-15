#include "../../../../include/Core/SDL/UI/UIText.h"
#include "../../../../include/Core/SDL/Renderer.h"
#include "../../../../include/Math/Vector2.h"


UIText::UIText(texturesID id, Fonts font, std::string text)
	: textID(id), font(font), Text(text)
{
	TextureManager::GetInstance()->SetTexture(id, nullptr);
}

void UIText::Update(Uint32 wrapSize)
{
	UIManager::GetInstance()->LoadText(textID, font, Text, color, wrapSize);
}

void UIText::Draw(Vector2 scale, bool center)
{
	if (center)
	{
		SDL_Rect dest
		{ 
			textRect.x - (textRect.w / 2), 
			textRect.y - (textRect.h / 2), 
			textRect.w, 
			textRect.h 
		};

		UIManager::GetInstance()->DrawText(textID, dest, scale);

#if _DEBUG
		// TODO: Remove magic numbers
		DrawTextBox(50, 80, 255, 255, dest);
#endif
	}
	else
	{
#if _DEBUG
		// TODO: Remove magic numbers
		DrawTextBox(50, 80, 255, 255, textRect);
#endif
		UIManager::GetInstance()->DrawText(textID, textRect, scale);
	}
}

void UIText::ChangeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void UIText::SetPos(int x, int y)
{
	textRect.x = x;
	textRect.y = y;
}

void UIText::SetWidthAndHeight(int w, int h)
{
	textRect.w = w;
	textRect.h = h;
}

void UIText::SetWidthAndHeightByText()
{
	SDL_QueryTexture(TextureManager::GetInstance()->GetTextureMap().at(textID), NULL, NULL, &textRect.w, &textRect.h);
}

void UIText::SetText(std::string newText)
{
	Text = newText;
}

SDL_Rect UIText::GetTextureDim()
{
	return textRect;
}

void UIText::DrawTextBox(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Rect textRect)
{
	SDL_SetRenderDrawColor(Renderer::GetInstance()->GetRenderer(), r, g, b, a);
	SDL_RenderDrawRect(Renderer::GetInstance()->GetRenderer(), &textRect);
}