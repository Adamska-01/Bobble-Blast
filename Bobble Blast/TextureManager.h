#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>
#include "Renderer.h"
#include "Vector2D.h"

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


class TextureManager
{
private:
	TextureManager() {
		//init IMG
		if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
			std::cout << "Error: " << IMG_GetError() << std::endl;
	};
	static TextureManager* Instance;

	std::map<texturesID, SDL_Texture*> TextureMap;

public:
	inline static TextureManager* GetInstance() { return Instance = (Instance != nullptr) ? Instance : new TextureManager(); }

	bool LoadTextures(std::string p_filename);

	void NormalDraw(texturesID p_id);
	void Draw(texturesID p_id, SDL_Rect p_dst, Vector2D p_scale, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
	void DrawPortion(texturesID p_id, SDL_Rect p_src, SDL_Rect p_dst, Vector2D p_scale, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
	void DrawFrame(texturesID p_id, SDL_Rect p_dst, Vector2D p_scale, int p_row, int p_frame, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
	void DrawTile(texturesID p_id, SDL_Rect src, SDL_Rect dst, int p_row, int p_frame, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
	void DrawRotate(texturesID p_id, Vector2D pos, Vector2D p_scale, float p_angle, SDL_Point rotPoint, SDL_RendererFlip p_flip = SDL_FLIP_NONE);

	void Drop(texturesID p_id);
	
	void Clean();

	//Getters
	inline std::map<texturesID, SDL_Texture*> GetTextureMap() { return TextureMap; };

	//Setters
	inline void SetTexture(texturesID p_id, SDL_Texture* p_texture) { TextureMap[p_id] = p_texture; }
};