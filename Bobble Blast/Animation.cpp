#include "Animation.h"
#include "TextureManager.h"

Animation::Animation()
{
}


bool Animation::Update(texturesID p_id, float dt)
{
	//Check if the animation is of "loop type" and is not started
	if (!AnimationDetails[p_id].repeat && !AnimationDetails[p_id].started)
	{
		AnimationDetails[p_id].started = true;
		AnimationDetails[p_id].spriteFrame += AnimationDetails[p_id].AnimSpeed * dt;
	}
	else
		AnimationDetails[p_id].spriteFrame += AnimationDetails[p_id].AnimSpeed * dt;
	
	//Restart the animation if completed (returns true) (first if for loop type animations)
	if ((int)AnimationDetails[p_id].spriteFrame >= AnimationDetails[p_id].FrameCount &&
		!AnimationDetails[p_id].repeat)
	{
		AnimationDetails[p_id].started = false;
		AnimationDetails[p_id].spriteFrame = 0;

		return true;
	}
	else if ((int)AnimationDetails[p_id].spriteFrame >= AnimationDetails[p_id].FrameCount)
	{
		AnimationDetails[p_id].spriteFrame = 0;

		return true;
	}

	return false; //Animation is not completed
}

void Animation::Draw(texturesID p_id, SDL_Rect dstRect, Vector2D p_scale, SDL_RendererFlip p_flip)
{
	TextureManager::GetInstance()->DrawFrame(p_id, dstRect, p_scale, AnimationDetails[p_id].spriteRow, AnimationDetails[p_id].spriteFrame, p_flip);
}

void Animation::SetProp(texturesID p_id, bool p_repeat, int Row, int p_FrameCount, int Row_Count, int p_speed, SDL_RendererFlip p_flip)
{
	AnimationDetails[p_id].repeat = p_repeat;
	AnimationDetails[p_id].spriteRow = Row;
	AnimationDetails[p_id].FrameCount = p_FrameCount;
	AnimationDetails[p_id].RowCount = Row_Count;
	AnimationDetails[p_id].AnimSpeed = p_speed;
}

void Animation::WidthAndHeightTexture(texturesID p_id, SDL_Rect& src)
{
	SDL_Rect srcRect;
	SDL_QueryTexture(TextureManager::GetInstance()->GetTextureMap()[p_id], NULL, NULL, &srcRect.w, &srcRect.h);

	//Get the size of a single frame in a sprite sheet
	src.w = round((float)srcRect.w / AnimationDetails[p_id].FrameCount);
	src.h = round((float)srcRect.h / AnimationDetails[p_id].RowCount);
}
