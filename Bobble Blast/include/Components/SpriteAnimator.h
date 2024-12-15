#pragma once
#include "../../include/Components/GameComponent.h"
#include "../Core/SDL/TextureManager.h"
#include "Generic/SpriteAnimationProperties.h"
#include <map>
#include <SDL.h>
#include <string>


class Vector2;


class SpriteAnimator : GameComponent
{
protected:
	SpriteAnimationProperties properties;

	std::map<texturesID, SpriteAnimationProperties> AnimationDetails;

	std::string TextureID = "";

public:
	SpriteAnimator() = default;

	// Temp
	virtual void Update(float dt) override {};
	virtual void Draw() override {};
	virtual void Clean() override {};

	bool Update(texturesID id, float dt);
	
	void Draw(texturesID id, SDL_Rect dest, Vector2 scale, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void SetProp(texturesID p_id, bool p_repeat, int Row, int p_FrameCount, int Row_Count, int p_speed, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
	
	SDL_Rect GetFrameRect(texturesID id);
	
	const SpriteAnimationProperties& GetProp();
};