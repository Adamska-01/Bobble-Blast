#include "../../include/Constants/ScreenConstants.h"
#include "../../include/Core/SDL/TextureManager.h"
#include "../../include/Game/Background.h"
#include "../../include/Math/Vector2.h"
#include <SDL.h>


Background::Background(texturesID background, Vector2 start, bool canScroll)
	: ID(background), canScroll(canScroll)
{
	//set camera and image rects
	srcCamera.x = start.x;
	srcCamera.y = start.y;
	srcCamera.w = ScreenConstants::SCREENWIDTH;
	srcCamera.h = ScreenConstants::SCREENHEIGHT;
	
	srcImage.x = 0;
	srcImage.y = 0;

	scrollingSpeed = 50;
	increment = 0;

	SDL_QueryTexture(TextureManager::GetInstance()->GetTextureMap().at(background), NULL, NULL, &srcImage.w, &srcImage.h);
}

void Background::Update(float dt)
{
	if (!canScroll)
		return;
	
	increment += scrollingSpeed * dt;
	if (increment >= 1.0f)
	{
		srcCamera.x += (int)increment;
		increment = 0;
	}

	if (srcCamera.x > srcImage.w - srcCamera.w)
	{
		srcCamera.x = 0;
	}
}

void Background::Draw()
{
	TextureManager::GetInstance()->DrawPortion(ID, srcCamera, srcImage, Vector2::One);
}