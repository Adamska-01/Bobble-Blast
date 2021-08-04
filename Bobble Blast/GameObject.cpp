#include "GameObject.h"

GameObject::GameObject()
{
	transform = new Transform();
}

GameObject::~GameObject()
{
	Clean();
}

void GameObject::Clean()
{
	if (transform != nullptr)
	{
		delete transform;
		transform = nullptr;
	}
}
