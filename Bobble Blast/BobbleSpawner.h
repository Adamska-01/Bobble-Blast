#pragma once
#include <vector>
#include "Bobble.h"
#include <fstream>
#include <sstream>
#include "Stats.h"


class BobbleSpawner
{
private:
	std::vector<Bobble*> bobbles;
	
	int startX;//, spriteWidth;

	float bobbleSpeed;

	//Timers
	SDL_TimerID timerID;
	SDL_TimerID timerID2;
	float speedMultiplier = 1.2f;

	//Player's Scores
	Stats* stats;
	int Score;
	int PenaltyScore;

public:
	BobbleSpawner(int p_startX);
	~BobbleSpawner();

	void Update(float dt);
	void Draw();

	void Clean();

	//Collisions
	void CollisionsWall(SDL_Rect wall, bool lavaWall = false);
	void CollisionsBobble(Bobble* b);

	//Timer based funtions
	void Spawn();
	void IncreaseSpeed();

private:
	void Blow(int index);

public:
	void RemoveTimers();

	//Getters
	inline Stats* GetStats() { return stats; }
};