#pragma once
#include <map>
#include <string>
#include <sdl.h>


enum class texturesID
{
	IDLE_BOBBLE,
	BLOW_BOBBLE,
	CANNON,
	ARROW,
	MAP1,
	BACKGROUND,
	MENU,
	P1_SCORE,
	P2_SCORE,
	FPS_COUNTER,
	END_GAME_TEXT,
	END_GAME_BACKGROUND,
	MAX_TEXTURES
};


class SDL_Point;
class Vector2;
struct SDL_Rect;
struct SDL_Texture;


class TextureManager
{
private:
	TextureManager();


	static TextureManager* Instance;


	std::map<texturesID, SDL_Texture*> TextureMap;


public:
	inline static TextureManager* GetInstance() { return Instance = (Instance != nullptr) ? Instance : new TextureManager(); }


	bool LoadTextures(std::string filename);

	void NormalDraw(texturesID id);
	
	void Draw(texturesID id, SDL_Rect dest, Vector2 scale, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void DrawPortion(texturesID id, SDL_Rect src, SDL_Rect dest, Vector2 scale, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void DrawFrame(texturesID id, SDL_Rect dest, Vector2 scale, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void DrawTile(texturesID id, SDL_Rect src, SDL_Rect dest, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void DrawRotate(texturesID id, Vector2 pos, Vector2 scale, float angle, SDL_Point rotPoint, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void Drop(texturesID id);
	
	void Clean();

	const std::map<texturesID, SDL_Texture*>& GetTextureMap();

	void SetTexture(texturesID id, SDL_Texture* texture);
};