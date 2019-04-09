#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "matrix_4x4.h"

inline const mat4 RotationX(float angle) {

	const float c = cosf(angle * math_radians), s = sinf(angle * math_radians);

	return mat4(1, 0, 0, 0,
	            0, c,-s, 0,
	            0, s, c, 0,
	            0, 0, 0, 1);
}

inline const mat4 RotationY(float angle) {

	const float c = cosf(angle * math_radians), s = sinf(angle * math_radians);

	return mat4(c, 0, s, 0,
	            0, 1, 0, 0,
	           -s, 0, c, 0,
	            0, 0, 0, 1);
}

inline const mat4 RotationZ(float angle) {

	const float c = cosf(angle * math_radians), s = sinf(angle * math_radians);

	return mat4(c,-s, 0, 0,
	            s, c, 0, 0,
	            0, 0, 1, 0,
	            0, 0, 0, 1);
}

inline const mat4 FromEuler(float x, float y, float z) {

	const float cx = cosf(x * math_radians), sx = sinf(x * math_radians),
	            cy = cosf(y * math_radians), sy = sinf(y * math_radians),
	            cz = cosf(z * math_radians), sz = sinf(z * math_radians);

	// rotationX * rotationY * rotationZ
	return mat4(cy * cz, -cy * sz, sy, 0,
	            cx * sz + sx * cz * sy, cx * cz - sx * sy * sz, -cy * sx, 0,
	            sx * sz - cx * cz * sy, cz * sx + cx * sy * sz, cx * cy, 0,
	            0, 0, 0, 1);
}

inline const mat4 FromEuler(const vec3 &r) {

	return FromEuler(r.x, r.y, r.z);
}

inline const vec3 ToEuler(const mat4 &M) {

	vec3 angle;
	float x, y, C;

	angle.y = asinf(M.m[2]);
	C       = cosf(angle.y);
	angle.y *= math_degrees;

	if (fabsf(C) > math_epsilon) {
	
		x       =  M.m[10] / C;
		y       = -M.m[ 6] / C;
		angle.x = atan2f(y, x) * math_degrees;
		x       =  M.m[ 0] / C;
		y       = -M.m[ 1] / C;
		angle.z = atan2f(y, x) * math_degrees;
	} else {
	
		angle.x = 0.0f;
		x       =  M.m[ 5];
		y       =  M.m[ 4];
		angle.z = atan2f(y, x) * math_degrees;
	}

	if (angle.x < 0) angle.x += 360;
	if (angle.y < 0) angle.y += 360;
	if (angle.z < 0) angle.z += 360;

	return angle;
}

inline const mat4 Scale(float x, float y, float z) {

	return mat4(x, 0, 0, 0,
	            0, y, 0, 0,
	            0, 0, z, 0,
	            0, 0, 0, 1);
}

inline const mat4 Scale(const vec3 &s) {

	return Scale(s.x, s.y, s.z);
}

inline const mat4 Translation(float x, float y, float z) {

	return mat4(1, 0, 0, x,
	            0, 1, 0, y,
	            0, 0, 1, z,
	            0, 0, 0, 1);
}

inline const mat4 Translation(const vec3 &t) {

	return Translation(t.x, t.y, t.z);
}

#endif // TRANSFORMATION_H