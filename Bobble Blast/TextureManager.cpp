#include "TextureManager.h"
#include <fstream>
#include <sstream>
#include "Debug.h"

TextureManager* TextureManager::Instance = nullptr;

bool TextureManager::LoadTextures(std::string p_filename)
{
    //open file
    std::ifstream file;
    file.open(p_filename);

    int ID = 0;

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

void TextureManager::NormalDraw(texturesID p_id)
{
    SDL_RenderCopy(Renderer::GetInstance()->GetRenderer(), TextureMap[p_id], NULL, NULL);
}

void TextureManager::Draw(texturesID p_id, SDL_Rect p_dst, Vector2D p_scale, SDL_RendererFlip p_flip)
{
    SDL_Rect srcRect = { 0, 0, p_dst.w, p_dst.h };

    SDL_Rect destRect = { p_dst.x, p_dst.y, p_dst.w * p_scale.x, p_dst.h * p_scale.y };

    SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), TextureMap[p_id], &srcRect, &destRect, 0, nullptr, p_flip);
}

void TextureManager::DrawPortion(texturesID p_id, SDL_Rect p_src, SDL_Rect p_dst, Vector2D p_scale, SDL_RendererFlip p_flip)
{
    SDL_Rect srcRect = { p_src.x, p_src.y, p_src.w, p_src.h };

    SDL_Rect destRect = { 0, 0, p_src.w * p_scale.x, p_src.h * p_scale.y };

    SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), TextureMap[p_id], &srcRect, &destRect, 0, nullptr, p_flip);

}

void TextureManager::DrawFrame(texturesID p_id, SDL_Rect p_dst, Vector2D p_scale, int p_row, int p_frame, SDL_RendererFlip p_flip)
{
    SDL_Rect srcRect = { p_dst.w * p_frame, p_dst .h * p_row, p_dst.w, p_dst.h };

    SDL_Rect destRect = { p_dst.x, p_dst.y, p_dst.w * p_scale.x, p_dst.h * p_scale.y };

    //SDL_RenderDrawRect(Renderer::GetInstance()->GetRenderer(), &destRect);
    SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), TextureMap[p_id], &srcRect, &destRect, 0, NULL, p_flip);
}

void TextureManager::DrawTile(texturesID p_id, SDL_Rect src, SDL_Rect dst, int p_row, int p_frame, SDL_RendererFlip p_flip)
{
    SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), TextureMap[p_id], &src, &dst, 0, nullptr, p_flip);
}

void TextureManager::DrawRotate(texturesID p_id, Vector2D pos, Vector2D p_scale, float p_angle, SDL_Point rotPoint, SDL_RendererFlip p_flip)
{
    SDL_Rect dstRect{ pos.x, pos.y, 0, 0 };

    SDL_QueryTexture(TextureMap[p_id], NULL, NULL, &dstRect.w, &dstRect.h);
    dstRect.w *= p_scale.x;
    dstRect.h *= p_scale.y;

    SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), TextureMap[p_id], NULL, &dstRect, p_angle, &rotPoint, p_flip);
}


void TextureManager::Drop(texturesID p_id)
{
    SDL_DestroyTexture(TextureMap[p_id]);
    TextureMap.erase(p_id);
}

void TextureManager::Clean()
{
    std::map<texturesID, SDL_Texture*>::iterator it;
    for (it = TextureMap.begin(); it != TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    TextureMap.clear();

#if _DEBUG
    DBG_ASSERT_MSG_EMPTY(TextureMap.size(), "DEBUG_MSG: TextureMap cleaned! \n");
#endif

    IMG_Quit();
}