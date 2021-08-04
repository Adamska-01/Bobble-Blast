#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "CircleCollider2D.h"
#include <conio.h>
#include <time.h>


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


class Bobble : public GameObject
{
private:
	CircleCollider2D circleCollider;
	SDL_Rect dstRect; 

	//Motion
	Vector2D Velocity;
	float speed;
	bool isFired;

	Vector2D SurfacePoint;

	Colour colour;

	std::map<Colour, std::string> TextureIDs;

	Animation* Anim;

	bool canExplode;
	bool canDestroy;
	bool canGoToGrid;

	static bool RandInit;

public:
	Bobble(Vector2D startPos);
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

private:
	void Bounce(Vector2D Normal);

public:
	//Setters
	inline void SetVelocity(Vector2D v) { Velocity = v; }
	inline void SetPosition(Vector2D v) {
		transform->position = v;
		circleCollider.SetPos(v);
	}
	inline void SetDestruction(bool value) { canExplode = value; }
	inline void SetSpeed(float value) { speed = value; }

	//Getters
	inline Circle GetCircle() { return circleCollider.GetCircle(); }
	inline bool CanDestroy() { return canDestroy; }
	inline bool CanExplode() { return canExplode; }
	inline bool IsFiring() { return isFired; }
	inline Colour GetColor() { return colour; }
};

