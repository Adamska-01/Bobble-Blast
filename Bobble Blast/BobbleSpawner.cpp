#include "BobbleSpawner.h"
#include "UsefullFunctions.h"
#include "Timer.h"
#include "AudioManager.h"

//TIMERS
unsigned int SpawnerTimer(unsigned int interval, void* param)
{
	static_cast<BobbleSpawner*>(param)->Spawn();
	return interval; // repeat the timer
}
unsigned int SpeedTimer(unsigned int interval, void* param)
{
	static_cast<BobbleSpawner*>(param)->IncreaseSpeed();
	return interval; // repeat the timer
}


BobbleSpawner::BobbleSpawner(int p_startX)
	: startX(p_startX)
{
	//Init score and lives 
	stats = new Stats();
	
	//Speed
	bobbleSpeed = 100.0f;
	
	//Player's Scores
	Score = 100;
	PenaltyScore = -50;

	//Timers
	BobbleSpawner* param = this;
	timerID = SDL_AddTimer(3.0f * 1000, SpawnerTimer, param);
	timerID2 = SDL_AddTimer(120 * 1000, SpeedTimer, param);
}

BobbleSpawner::~BobbleSpawner()
{
	Clean();
}

void BobbleSpawner::Update(float dt)
{
	//Updates every bobble and checks if any can be deleted
	for (int i = 0; i < bobbles.size(); i++)
	{
		bobbles[i]->Update(dt);

		Blow(i);
	}
}

void BobbleSpawner::Draw()
{
	for (int i = 0; i < bobbles.size(); i++)
	{
		bobbles[i]->Draw();
	}
}

void BobbleSpawner::Clean()
{
	if (bobbles.size() > 0)
	{
		for (int i = 0; i < bobbles.size(); i++)
		{
			delete bobbles[i];
			bobbles[i] = nullptr;
		}
		bobbles.clear();
	}

	RemoveTimers();
}

void BobbleSpawner::CollisionsWall(SDL_Rect wall, bool lavaWall)
{
	for (int i = 0; i < bobbles.size(); i++)
	{
			//Baunce
		if (bobbles[i]->CollisionsWithWall(wall))
			if(lavaWall && bobbles[i]->IsFiring()) 
			{	//If lava
				bobbles[i]->StopFire();
				bobbles[i]->SetDestruction(true);

				//Update stats
				if (stats->GetLives() > 0)
				{
					stats->AddScore(PenaltyScore);
					stats->AddLives(-1);
				}

				AudioManager::GetInstance()->PlaySFX(0, 0, 0);
			}
			else if(!lavaWall)
				AudioManager::GetInstance()->PlaySFX(2, 0, 0);
	}
}

void BobbleSpawner::CollisionsBobble(Bobble* b)
{
	if(b != nullptr && b->IsFiring())
		for (int i = 0; i < bobbles.size(); i++)
		{
			//If there is a collision and the colour doesn't match
			if (bobbles[i]->CollisionsWithBall(b->GetCircle()) && bobbles[i]->GetColor() != b->GetColor() && !bobbles[i]->CanExplode())
			{
				b->StopFire();
				b->SetDestruction(true);

				if (stats->GetLives() > 0) stats->AddScore(PenaltyScore);
				AudioManager::GetInstance()->PlaySFX(0, 0, 0);
			}
			//Same but the colour does match
			else if (bobbles[i]->CollisionsWithBall(b->GetCircle()) && bobbles[i]->GetColor() == b->GetColor() && !bobbles[i]->CanExplode())
			{
				bobbles[i]->StopFire();
				bobbles[i]->SetDestruction(true);
			
				b->StopFire();
				b->SetDestruction(true);

				if (stats->GetLives() > 0) stats->AddScore(Score);
				AudioManager::GetInstance()->PlaySFX(0, 0, 0);
			}
		}
}

void BobbleSpawner::Spawn()
{
	//Instantiate bobble
	Vector2D pos(startX, 0);
	bobbles.push_back(new Bobble(pos));

	//Set Velocity
	Vector2D vel(UsefullFunctions::RandomFloat(-1, 1), UsefullFunctions::RandomFloat(0.2f, 1));
	bobbles.back()->SetVelocity(vel.Normal(Zero));

	//Set speed
	bobbles.back()->SetSpeed(bobbleSpeed);

	//Start motion
	bobbles.back()->Fire();

	AudioManager::GetInstance()->PlaySFX(1, 0, 4);
}



void BobbleSpawner::Blow(int index)
{
	//Destroys the bobble if it can be destroyed
	if (bobbles[index] != nullptr && bobbles[index]->CanDestroy())
	{
		delete bobbles[index];
		bobbles[index] = nullptr;

		bobbles.erase(bobbles.begin() + index);
	}
}

void BobbleSpawner::IncreaseSpeed()
{
	bobbleSpeed *= speedMultiplier;
}

void BobbleSpawner::RemoveTimers()
{
	SDL_RemoveTimer(timerID);
	SDL_RemoveTimer(timerID2);
}
