#pragma once
#include "GameObject.h"
#include "Bobble.h"
#include "UsefullFunctions.h"
#include "Stats.h"


class Cannon : public GameObject
{
private:
	//Rotation
	float rotationSpeed;
	float minRot;
	float maxRot;

	Vector2D RotationPos;	//Rotation point (Cannon)
	Vector2D Direction;		//Direction vector (Arrow)

	Transform* CannonT;
	
	SDL_Rect canRect;
	SDL_Rect arrowRect;

	Bobble* bobble;

	SDL_Point rotPoint;		//SDL has a data type for the rotation point 

	//Controller number
	int WhatPlayer;

	bool gameOver = false;

public:
	Cannon(Vector2D p_pos, int p_whatPlayer);
	~Cannon();

	void Update(float dt) override;
	void Draw() override;
	void Clean() override;

	//Setters
	inline void SetGameover(bool value) { gameOver = value; }

	//Getters
	inline bool GetGameOver() { return gameOver; }
	inline Bobble* GetBobble() { return bobble; }
};