#pragma once
#include <SDL.h>
#include "CircleCollider2D.h"


class CollisionHandler
{
private:
	CollisionHandler() {};
	static CollisionHandler* Instance;

public:
	inline static CollisionHandler* GetInstance() { return Instance = (Instance != nullptr) ? Instance : new CollisionHandler(); }

	bool BoxToBoxCollision(SDL_Rect A, SDL_Rect B);
	bool CircleToBoxCollision(Circle A, SDL_Rect B, Vector2D& P);
	bool CircleToCircleCollision(Circle A, Circle B);
};
