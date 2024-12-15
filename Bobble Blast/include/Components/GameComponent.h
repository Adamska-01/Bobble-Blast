#pragma once


class GameObject;


class GameComponent
{
public:
	GameObject* OwningObject;


	GameComponent() = default;

	GameComponent(GameComponent&& other) = default;

	virtual ~GameComponent() = default;


	virtual void Update(float dt) {};

	virtual void Draw() {};


protected:
	virtual void Clean() {};
};