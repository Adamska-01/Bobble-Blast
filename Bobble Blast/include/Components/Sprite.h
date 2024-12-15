#pragma once
#include "GameComponent.h"


class Sprite : public GameComponent
{
public:
	Sprite() = default;
	
	Sprite(Sprite&& other) = default;

	~Sprite() override = default;


	void Update(float dt) override {};

	void Draw() override {};


protected:
	virtual void Clean() override {};
};