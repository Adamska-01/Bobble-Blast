#include "../../include/Components/Generic/SpriteAnimationProperties.h"


SpriteAnimationProperties::SpriteAnimationProperties()
	: repeat(true),
	started(false),
	spriteFrame(0.0f),
	spriteRow(0), animSpeed(0),
	frameCount(0), 
	rowCount(0), 
	flip(SDL_FLIP_NONE)
{
}

SpriteAnimationProperties::SpriteAnimationProperties(
	bool repeat,
	bool started,
	int spriteRow,
	float spriteFrame,
	int animSpeed,
	int frameCount,
	int rowCount,
	SDL_RendererFlip flip)
		: repeat(repeat),
		started(started),
		spriteRow(spriteRow),
		spriteFrame(spriteFrame),
		animSpeed(animSpeed),
		frameCount(frameCount),
		rowCount(rowCount),
		flip(flip)
{
}

void SpriteAnimationProperties::Reset()
{
	repeat = true;
	started = false;
	spriteRow = 0;
	spriteFrame = 0.0f;
	animSpeed = 0;
	frameCount = 0;
	rowCount = 0;
	flip = SDL_FLIP_NONE;
}