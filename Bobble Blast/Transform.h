#pragma once
#include "Vector2D.h"

#define PI 3.14159265358979323846

class Transform
{
public:
	Transform(Vector2D p_pos = Zero, Vector2D p_scale = One, float p_angle = 0.0f) {
		position = p_pos;
		scale = p_scale;
		angle = p_angle;
	}

	Vector2D position;
	Vector2D scale;
	float angle = 0.0f;


	inline void Log(std::string msg = "") {
		std::cout << msg << "(X Y) = (" << position.x << " " << position.y << ")" << std::endl;
	}

	inline void TranslateX(float p_x) { position.x += p_x; }
	inline void TranslateY(float p_y) { position.y += p_y; }
	inline void Translate(Vector2D v) { position.x += v.x; position.y += v.y; }

	inline void ScaleX(float p_x) { scale.x* p_x; }
	inline void ScaleY(float p_y) { scale.y* p_y; }
	inline void Scale(Vector2D v) { scale.x* v.x; scale.y* v.y; }

	inline void Rotate(float p_angle) { angle += p_angle * (PI / 180); };

	inline float GetAngle() { return angle; }
	inline float getAngle(Vector2D v1, Vector2D v2) {
		angle =  atan2(v1.y - v2.y, v1.x - v2.x) * (PI / 180);
		return angle >= 0 ? angle : 360 + angle;
	}
};