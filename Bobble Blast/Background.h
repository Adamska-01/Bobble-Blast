#pragma once
#include "TextureManager.h"


class Background
{
private:
	SDL_Rect srcCamera;
	SDL_Rect srcImage;
	
	texturesID ID;

	//Scrolling 
	bool Scroll;
	float ScrollingSpeed;
	float increment;

public:
	Background(texturesID p_background, Vector2D start, bool p_scroll = false);
	~Background();

	void Update(float dt);
	void Draw();
};