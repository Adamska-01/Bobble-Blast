#pragma once
#include <SDL.h>


struct SpriteAnimationProperties
{
	bool repeat;

	bool started;

	float spriteFrame;

	int spriteRow;

	int animSpeed;

	int frameCount;

	int rowCount;

	SDL_RendererFlip flip;


	SpriteAnimationProperties();
		

	SpriteAnimationProperties(
		bool repeat,
		bool started,
		int spriteRow,
		float spriteFrame,
		int animSpeed,
		int frameCount,
		int rowCount,
		SDL_RendererFlip flip);


	void Reset();
};