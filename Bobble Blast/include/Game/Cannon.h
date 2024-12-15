#pragma once
#include "Bobble.h"
#include "Stats.h"


class Vector2;


class Cannon : public GameObject
{
private:
	float rotationSpeed;
	
	float minRot;
	
	float maxRot;

	Vector2 RotationPos;	//Rotation point (Cannon)
	
	Vector2 Direction;		//Direction vector (Arrow)

	Transform* CannonT;
	
	SDL_Rect canRect;

	SDL_Rect arrowRect;

	Bobble* bobble;

	SDL_Point rotPoint;		//SDL has a data type for the rotation point 

	//Controller number
	int WhatPlayer;

	bool gameOver;


public:
	Cannon(Vector2 pos, int whatPlayer);

	~Cannon();


	void Update(float dt) override;
	
	void Draw() override;
	
	void Clean() override;

	inline void SetGameover(bool value) { gameOver = value; }

	inline bool GetGameOver() { return gameOver; }
	
	inline Bobble* GetBobble() { return bobble; }
};