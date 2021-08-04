#pragma once
#include "Cannon.h"
#include "Map.h"
#include "AudioManager.h"


class Application
{
private:
	bool Running{ false };
	bool gameover{ false };
	bool TwoPlayers{ false };
	
	//Player
	std::vector<Cannon*> cannon{ nullptr };
	
	Map* map{ nullptr };

	Background* MenuBackground;
	
	UIText* FPSText;
	UIText* GameOverText;

public:
	Application();
	~Application();

	void Update();

private:
	void MenuUpdate();
	void Quit();
	void Destroy();
	SDL_Texture* EndGameFadeTexture();
	
public:
	//Getters
	inline bool IsRunning() { return Running; }
};



