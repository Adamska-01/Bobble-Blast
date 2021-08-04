#pragma once
#include "Vector2D.h"

struct Circle
{
	Vector2D pos;
	float r;
};


class CircleCollider2D
{
private:
	Circle collider;

public:
	CircleCollider2D() {};
	~CircleCollider2D() {};

	//Getters
	inline Circle GetCircle() { return collider; }

	//Setters
	inline void SetPos(Vector2D p_pos) { collider.pos = p_pos; }
	inline void SetSize(float p_value) { collider.r = p_value; }
};
