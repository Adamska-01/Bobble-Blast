#include "../../include/Components/SpriteAnimator.h"
#include "../../include/Math/Vector2.h"


bool SpriteAnimator::Update(texturesID id, float dt)
{
	auto& properties = AnimationDetails[id];

	//Check if the animation is of "loop type" and is not started
	if (!properties.repeat && !properties.started)
	{
		properties.started = true;
		properties.spriteFrame += properties.animSpeed * dt;
	}
	else
	{
		properties.spriteFrame += properties.animSpeed * dt;
	}
	
	//Restart the animation if completed (returns true) (first if for loop type animations)
	if ((int)properties.spriteFrame >= properties.frameCount && !properties.repeat)
	{
		properties.started = false;
		properties.spriteFrame = 0;

		return true;
	}
	else if ((int)properties.spriteFrame >= properties.frameCount)
	{
		properties.spriteFrame = 0;

		return true;
	}

	//Animation is not completed
	return false;
}

void SpriteAnimator::Draw(texturesID id, SDL_Rect dest, Vector2 scale, SDL_RendererFlip flip)
{
	auto& properties = AnimationDetails[id];
	
	TextureManager::GetInstance()->DrawFrame(id, dest, scale, properties.spriteRow, properties.spriteFrame, flip);
}

void SpriteAnimator::SetProp(texturesID id, bool repeat, int row, int frameCount, int rowCount, int speed, SDL_RendererFlip flip)
{
	AnimationDetails[id].repeat = repeat;
	AnimationDetails[id].spriteRow = row;
	AnimationDetails[id].frameCount = frameCount;
	AnimationDetails[id].rowCount = rowCount;
	AnimationDetails[id].animSpeed = speed;
}

SDL_Rect SpriteAnimator::GetFrameRect(texturesID id)
{
	SDL_Rect srcRect;
	SDL_QueryTexture(TextureManager::GetInstance()->GetTextureMap().at(id), NULL, NULL, &srcRect.w, &srcRect.h);

	//Get the size of a single frame in a sprite sheet
	srcRect.w = round((float)srcRect.w / AnimationDetails[id].frameCount);
	srcRect.h = round((float)srcRect.h / AnimationDetails[id].rowCount);

	return srcRect;
}

const SpriteAnimationProperties& SpriteAnimator::GetProp()
{
	return properties;
}