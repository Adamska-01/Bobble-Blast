#pragma once
#include <iostream>
#include <vector>
#include <SDL_mixer.h>
#include "Debug.h"


enum type
{
	MUSIC, SFX
};

class AudioManager
{
private:
	inline AudioManager() {
		//frequency value (KHz), audio format, number of channels, total chunk size (sample size)
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512);
	}
	static AudioManager* Instance;

	std::vector<Mix_Chunk*> Sfx;
	std::vector<Mix_Music*> Music;

	//Music and SFX holders
	Mix_Music* music;
	Mix_Chunk* sfx;

public:
	inline static AudioManager* GetInstance() { return Instance = (Instance != nullptr) ? Instance : new AudioManager(); }

	bool LoadAudio(int p_id, std::string p_filename, type p_audioType, int p_volume);
	void PlayMusicTrack(int p_id, int p_loopNumber);
	void PlaySFX(int p_id, int p_loopNumber, int p_channel);
	void FadeMusicTrack(int p_id, int p_loopNumber, int p_fadeLenght);

	void StopMusic();

	void Clean();
};