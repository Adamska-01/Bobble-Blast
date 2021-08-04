#include "UIManager.h"
#include <fstream>
#include <sstream>

UIManager* UIManager::Instance = nullptr;

bool UIManager::LoadFonts(Fonts p_id, std::string p_textPath, int p_fontsize)
{
    FontList[p_id] = TTF_OpenFont(p_textPath.c_str(), p_fontsize);

#if _DEBUG
        DBG_ASSERT_MSG(FontList[p_id], "Failed to load the text: % s\n", TTF_GetError());
#endif

    return true;
}

bool UIManager::LoadText(texturesID p_id, Fonts p_font, std::string p_text, SDL_Color p_color, Uint32 p_wrapsize)
{
    if (p_wrapsize <= 0) p_wrapsize = 1;
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(FontList[p_font], p_text.c_str(), p_color, p_wrapsize);

#if _DEBUG
    DBG_ASSERT_MSG(textSurface, "Failed to load the texture: % s\n", TTF_GetError());
#endif


    SDL_Texture* text = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetRenderer(), textSurface);

#if _DEBUG
    DBG_ASSERT_MSG(text, "Failed to create the texture: % s\n", TTF_GetError());
#endif

    //deleting temp surface
    SDL_FreeSurface(textSurface);
    textSurface = nullptr;
    //deleting previous texture
    SDL_DestroyTexture(TextureManager::GetInstance()->GetTextureMap()[p_id]);
    TextureManager::GetInstance()->SetTexture(p_id, nullptr);

    //Assign Updated text
    TextureManager::GetInstance()->SetTexture(p_id, text);

    return true;
}

void UIManager::DrawText(texturesID p_id, SDL_Rect p_dst, Vector2D p_scale, SDL_RendererFlip p_flip)
{
    SDL_Rect destRect = { p_dst.x, p_dst.y, p_dst.w * p_scale.x, p_dst.h * p_scale.y };

    SDL_RenderCopy(Renderer::GetInstance()->GetRenderer(), TextureManager::GetInstance()->GetTextureMap()[p_id], NULL, &destRect);
}

void UIManager::Clean()
{
    std::map<Fonts, TTF_Font*>::iterator it;
    for (it = FontList.begin(); it != FontList.end(); it++)
        TTF_CloseFont(it->second);

    FontList.clear();

#if _DEBUG
    DBG_ASSERT_MSG_EMPTY(FontList.size(), "DEBUG_MSG: FontList cleaned! \n");
#endif

    TTF_Quit();
}
