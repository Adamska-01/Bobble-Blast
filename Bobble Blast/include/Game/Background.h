#pragma once


class Vector2;
struct SDL_Rect;


class Background
{
private:
	SDL_Rect srcCamera;

	SDL_Rect srcImage;
	
	texturesID ID;

	bool canScroll;
	
	float scrollingSpeed;
	
	float increment;


public:
	Background(texturesID background, Vector2 start, bool canScroll = false);

	~Background() = default;


	void Update(float dt);

	void Draw();
};