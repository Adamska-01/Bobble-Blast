#include "../../include/Components/Transform.h"
#include "../../include/Core/GameObject.h"


GameObject::GameObject()
{
	transform = &AddComponent<Transform>();
}

GameObject::~GameObject()
{
	Clean();
}

void GameObject::Update(float dt)
{
	transform->Update(dt);

	for (auto& component : componentBucket.components)
	{
		component->Update(dt);
	}
}

void GameObject::Draw()
{
	transform->Draw();

	for (auto& component : componentBucket.components)
	{
		component->Draw();
	}
}

void GameObject::Clean()
{
	// ?? 
	//gameComponents.clear();
}