#include "../../../include/Components/Collisions/Circle.h"
#include "../../../include/Math/Vector2.h"
#include "../../../include/Math/MathConstants.h"


Circle::Circle()
	: position(Vector2::Zero), radius(1.0f)
{
}

Circle::Circle(const Vector2& pos, float r) 
	: position(pos), radius(r) 
{
}

float Circle::Area() const 
{
	return MathConstants::PI * radius * radius;
}

float Circle::Circumference() const 
{
	return 2.0f * MathConstants::PI * radius;
}