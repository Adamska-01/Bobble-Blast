#include "AudioManager.h"

AudioManager* AudioManager::Instance = nullptr;

bool AudioManager::LoadAudio(int p_id, std::string p_filename, type p_audioType, int p_volume)
{
	if (p_audioType == MUSIC)
	{
		music = Mix_LoadMUS(p_filename.c_str());
		if (!music)
		{
			std::cout << "Unable to load music file: " << Mix_GetError() << std::endl;
			return false;
		}
		Music.push_back(music);
		Mix_VolumeMusic(p_volume);
		return true;
	}
	else if (p_audioType == SFX)
	{
		sfx = Mix_LoadWAV(p_filename.c_str());
		if (!sfx)
		{
			std::cout << "Unable to load SFX file: " << Mix_GetError() << std::endl;
			return false;
		}
		Mix_VolumeChunk(sfx, p_volume);
		Sfx.push_back(sfx);
		return true;
	}

	return false;
}

void AudioManager::PlayMusicTrack(int p_id, int p_loopNumber)
{
	Mix_PlayMusic(Music[p_id], p_loopNumber); //-1 to loop continuously
}

void AudioManager::PlaySFX(int p_id, int p_loopNumber, int p_channel)
{
	while (Mix_Playing(p_channel))
	{
		++p_channel;
	}

	if (!Mix_Playing(p_channel)) //-1 checking every channel
	{
		Mix_PlayChannel(p_channel, Sfx[p_id], p_loopNumber); //-1 to loop continuously
	}
}

void AudioManager::FadeMusicTrack(int p_id, int p_loopNumber, int p_fadeLenght)
{
	if (Mix_PlayingMusic())
	{
		Mix_FadeOutMusic(p_fadeLenght);
	}
	Mix_FadeInMusic(Music[p_id], p_loopNumber, p_fadeLenght); //fade in milliseconds
}

void AudioManager::StopMusic()
{
	Mix_HaltMusic();
}

void AudioManager::Clean()
{
	if (&Music != nullptr)
	{
		for (int i = 0; i < Music.size(); i++)
		{
			Mix_FreeMusic(Music[i]);
		}
		Music.clear();
	}
	if (&Sfx != nullptr)
	{
		for (int i = 0; i < Sfx.size(); i++)
		{
			Mix_FreeChunk(Sfx[i]);
		}
		Sfx.clear();
	}

	//No need to delete the holders
	music = nullptr;
	sfx = nullptr;

#if _DEBUG
	DBG_ASSERT_MSG_EMPTY(Music.size(), "DEBUG_MSG: Music cleaned! \n");
	DBG_ASSERT_MSG_EMPTY(Sfx.size(), "DEBUG_MSG: SFX cleaned! \n");
#endif

	Mix_CloseAudio();
}
