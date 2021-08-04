#pragma once
//interface object 


class IObject
{
public:
	//Pure virtual functions
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void Clean() = 0;
};