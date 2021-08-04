#include <cmath>
#include "Vector2D.h"

Vector2D::Vector2D()
	: x(0), y(0)
{
}

Vector2D::Vector2D(float x, float y)
	: x(x), y(y)
{
}

Vector2D& Vector2D::operator=(const Vector2D& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2D Vector2D::operator+(const Vector2D& v) const
{
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::operator*(const Vector2D& v) const
{
	return Vector2D(x * v.x, y * v.y);
}

Vector2D Vector2D::operator/(const Vector2D& v) const
{
	return Vector2D(x / v.x, y / v.y);
}

Vector2D Vector2D::operator*(const float& scalar) const
{
	return Vector2D(x * scalar, y * scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

bool Vector2D::operator==(const Vector2D& v) const
{
	if (this->x == v.x && this->y == v.y)
		return true;
	return false;
}

float Vector2D::dist(const Vector2D& v) const
{
	return static_cast<float>(std::sqrt((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)));
}

float Vector2D::Magnitude(const Vector2D& v)
{
	return static_cast<float>(std::sqrt(((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y))));
}

Vector2D& Vector2D::Normal(const Vector2D& magOrigin)
{
	float magnitude = Magnitude(magOrigin);
	
	x /= magnitude;
	y /= magnitude;

	return *this;
}

float Vector2D::Dot(const Vector2D& v)
{
	return ((x * v.x) + (y * v.y));
}

std::ostream& operator<<(std::ostream& out, const Vector2D& v)
{
	out << "(" << v.x << ", " << v.y << ")" << std::endl;
	return out;
}
