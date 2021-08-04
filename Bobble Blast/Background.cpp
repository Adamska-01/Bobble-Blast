#include "Background.h"

Background::Background(texturesID p_background, Vector2D start, bool p_scroll)
	: ID(p_background), Scroll(p_scroll)
{
	//set camera and image rects
	srcCamera.x = start.x;		
	srcCamera.y = start.y;		
	srcCamera.w = SCREENWIDTH;
	srcCamera.h = SCREENHEIGHT;
	
	srcImage.x = 0;
	srcImage.y = 0;
	SDL_QueryTexture(TextureManager::GetInstance()->GetTextureMap()[p_background], NULL, NULL, &srcImage.w, &srcImage.h);
	
	ScrollingSpeed = 50;
	increment = 0;
}

Background::~Background()
{
}

void Background::Update(float dt)
{
	if (Scroll) //only on the x
	{
		increment += ScrollingSpeed * dt;
		if (increment >= 1.0f)
		{
			srcCamera.x += (int)increment;
			increment = 0;
		}

		if (srcCamera.x > srcImage.w - srcCamera.w)
			srcCamera.x = 0;
	}
}

void Background::Draw()
{
	TextureManager::GetInstance()->DrawPortion(ID, srcCamera, srcImage, One);
}
