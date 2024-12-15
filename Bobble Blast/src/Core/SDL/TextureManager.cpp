#include "../../../include/Debugging/Debug.h"
#include "../../include/Core/SDL/Renderer.h"
#include "../../include/Core/SDL/TextureManager.h"
#include "../../include/Math/Vector2.h"
#include <fstream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>


TextureManager* TextureManager::Instance = nullptr;


TextureManager::TextureManager()
{
	auto initFlags = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	if ((initFlags & (IMG_INIT_PNG | IMG_INIT_JPG)) != (IMG_INIT_PNG | IMG_INIT_JPG)) 
	{
		std::cerr << "Failed to initialize SDL_image with PNG/JPG support! Error: " << IMG_GetError() << std::endl;
	}
};

bool TextureManager::LoadTextures(std::string filename)
{
	std::ifstream file;

	file.open(filename);

	auto ID = 0;

	std::string line;

	while (std::getline(file, line))
	{
		SDL_Surface* tempSurface = IMG_Load(line.c_str());

#if _DEBUG
		DBG_ASSERT_MSG(tempSurface, "Failed to load the surface: % s\n", SDL_GetError());
#endif

		SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetRenderer(), tempSurface);
		
#if _DEBUG
		DBG_ASSERT_MSG(texture, "Failed to create the texture: %s\n", SDL_GetError());
#endif

		SDL_FreeSurface(tempSurface);
		tempSurface = nullptr;

		TextureMap[static_cast<texturesID>(ID)] = texture;
		++ID;
	}

	return true;
}

void TextureManager::NormalDraw(texturesID id)
{
	SDL_RenderCopy(Renderer::GetInstance()->GetRenderer(), TextureMap[id], NULL, NULL);
}

void TextureManager::Draw(texturesID id, SDL_Rect dest, Vector2 scale, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0, 0, dest.w, dest.h };

	SDL_Rect destRect = { dest.x, dest.y, dest.w * scale.x, dest.h * scale.y };

	SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::DrawPortion(texturesID id, SDL_Rect src, SDL_Rect dest, Vector2 scale, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { src.x, src.y, src.w, src.h };

	SDL_Rect destRect = { 0, 0, dest.w * scale.x, dest.h * scale.y };

	SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(texturesID id, SDL_Rect dest, Vector2 scale, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { dest.w * frame, dest.h * row, dest.w, dest.h };

	SDL_Rect destRect = { dest.x, dest.y, dest.w * scale.x, dest.h * scale.y };

	SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), TextureMap[id], &srcRect, &destRect, 0, NULL, flip);
}

void TextureManager::DrawTile(texturesID id, SDL_Rect src, SDL_Rect dest, int row, int frame, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), TextureMap[id], &src, &dest, 0, nullptr, flip);
}

void TextureManager::DrawRotate(texturesID id, Vector2 pos, Vector2 scale, float angle, SDL_Point rotPoint, SDL_RendererFlip flip)
{
	SDL_Rect destRect{ pos.x, pos.y, 0, 0 };

	SDL_QueryTexture(TextureMap[id], NULL, NULL, &destRect.w, &destRect.h);

	destRect.w *= scale.x;
	destRect.h *= scale.y;

	SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), TextureMap[id], NULL, &destRect, angle, &rotPoint, flip);
}

void TextureManager::Drop(texturesID id)
{
	SDL_DestroyTexture(TextureMap[id]);

	TextureMap.erase(id);
}

void TextureManager::Clean()
{
	for (auto it = TextureMap.begin(); it != TextureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}

	TextureMap.clear();

#if _DEBUG
	DBG_ASSERT_MSG_EMPTY(TextureMap.size(), "DEBUG_MSG: TextureMap cleaned! \n");
#endif

	IMG_Quit();
}

const std::map<texturesID, SDL_Texture*>& TextureManager::GetTextureMap() 
{
	return TextureMap;
}

void TextureManager::SetTexture(texturesID id, SDL_Texture* texture)
{ 
	TextureMap[id] = texture;
}