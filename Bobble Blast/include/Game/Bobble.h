#pragma once
#include "../../include/Components/Collisions/CircleCollider2D.h"
#include "../../include/Core/GameObject.h"
#include <map>
#include <SDL_rect.h>
#include <string>


enum class Colour
{
	Black,
	Blue,
	Green,
	Grey,
	Orange,
	Purple,
	Red,
	Yellow,
	ALL_COLOURS
};


class SpriteAnimator;
struct Circle;


class Bobble : public GameObject
{
private:
	static bool RandInit;


	CircleCollider2D circleCollider;
	
	SDL_Rect dstRect; 

	Vector2 Velocity;
	
	float speed;
	
	bool isFired;

	Vector2 SurfacePoint;

	Colour colour;

	std::map<Colour, std::string> TextureIDs;

	SpriteAnimator* Anim;

	bool canExplode;
	
	bool canDestroy;
	
	bool canGoToGrid;


	void Bounce(Vector2 Normal);


public:
	Bobble(Vector2 startPos);
	
	~Bobble();


	void Update(float dt) override;

	void Draw() override;
	
	void Clean() override;

	void AnimationStateMachine();

	bool CollisionsWithWall(SDL_Rect wall);
	
	bool CollisionsWithBall(Circle ball);

	void Fire();
	
	void ChangeColour(int changeValue);
	
	void StopFire();

	void SetVelocity(Vector2 v);
	
	void SetPosition(Vector2 v);
	
	void SetDestruction(bool value);
	
	void SetSpeed(float value);

	Circle GetCircle();
	
	bool CanDestroy();
	
	bool CanExplode();
	
	bool IsFiring();
	
	Colour GetColor();
};