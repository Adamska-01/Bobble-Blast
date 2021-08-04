#pragma once
#include <iostream>

class Vector2D
{
public:
	float x = 0.0f;
	float y = 0.0f;

	Vector2D();
	Vector2D(float x, float y);
	~Vector2D() {}

	// basic functions
	float dist(const Vector2D& v) const;
	float Magnitude(const Vector2D& v); //return magnitude from v 
	Vector2D& Normal(const Vector2D& magOrigin);
	float Dot(const Vector2D& v);
	bool empty() { return (x == 0 && y == 0) ? true : false; }

	/*The following operators simply return Vector2ds that
	  have operations performed on the relative (x, y) values*/
	Vector2D& operator=(const Vector2D&);

	Vector2D operator+(const Vector2D&) const;
	Vector2D operator-(const Vector2D&) const;
	Vector2D operator*(const Vector2D&) const;
	Vector2D operator/(const Vector2D&) const;

	Vector2D operator*(const float& scalar) const;

	Vector2D& operator+=(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D& operator*=(const Vector2D& v);
	Vector2D& operator/=(const Vector2D& v);

	bool operator==(const Vector2D& v) const;

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v);
};

const Vector2D Zero(0, 0);
const Vector2D One(1, 1);