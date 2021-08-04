#pragma once
#include "IObject.h"
#include "Transform.h"

class GameObject : public IObject
{
protected:
	Transform* transform{ nullptr };

public:
	GameObject();
	~GameObject();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void Clean();
};