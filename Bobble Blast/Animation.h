#pragma once
#include <string>
#include "TextureManager.h"

//Property per sprite sheet/frame
struct Properties
{
	bool repeat{ true }; bool started{ false };

	int spriteRow{ 0 }; float spriteFrame{ 0.0f };
	int AnimSpeed{ 0 }, FrameCount{ 0 }, RowCount{ 0 };
	SDL_RendererFlip flip;
};

class Animation
{
protected:
	Properties properties;

	std::map<texturesID, Properties> AnimationDetails;
	std::string TextureID = "";

public:
	Animation();

	bool Update(texturesID p_id, float dt);
	void Draw(texturesID p_id, SDL_Rect dstRect, Vector2D p_scale, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
	void SetProp(texturesID p_id, bool p_repeat, int Row, int p_FrameCount, int Row_Count, int p_speed, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
	void WidthAndHeightTexture(texturesID p_id, SDL_Rect& src);
	
	//Getters
	inline Properties GetProp() { return properties; }
};