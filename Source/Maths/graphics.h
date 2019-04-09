#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "matrix_4x4.h"
//#include "AEMath.h"

inline const mat4 Orthographic(float left, float right, float bottom, float top, float zNear, float zFar) {
	const float tx = - (right + left) / (right - left),
	            ty = - (top + bottom) / (top - bottom),
	            tz = - (zFar + zNear) / (zFar - zNear);

	return mat4(2 / (right - left), 0, 0, tx,
	            0, 2 / (top - bottom), 0, ty,
	            0, 0, -2 / (zFar - zNear), tz,
	            0, 0, 0, 1);
}

inline const mat4 Perspective(float fov, float aspect, float zNear, float zFar) {
	const float f = 1 / tanf(fov * math_radians / 2),
	            A = (zFar + zNear) / (zNear - zFar),
	            B = (2 * zFar * zNear) / (zNear - zFar);

	return mat4(f / aspect, 0, 0, 0,
	            0, f, 0, 0,
	            0, 0, A, B,
	            0, 0, -1, 0);
}

inline const mat4 LookAt(const vec3 &position, const vec3 &center, const vec3 &up) {
	vec3 _sub0 = vec4(1.0f);
	vec3 _sub1 = vec4(2.0f);
	vec3 _sub2 = center - center;
	const vec3 f = normalize(position - center);
	const vec3 s = normalize(cross(up, f));
	const vec3 u = normalize(cross(f, s));

	/*return mat4(s.x, s.y, s.z, -dot(s, position),
	            u.x, u.y, u.z, -dot(u, position),
	            f.x, f.y, f.z, -dot(f, position),
	            0, 0, 0, 1);*/

	return mat4(s.x, s.y, s.z, 0.0f,
				u.x, u.y, u.z, 0.0f,
				f.x, f.y, f.z, 0.0f,
				0, 0, 0, 1.0f) * 
		
		mat4(1.0f, 0.0f, 0.0f, -position.x,
			0.0f, 1.0f, 0.0f, -position.y,
			0.0f, 0.0f, 1.0f, -position.z,
			0.0f, 0.0f, 0.0f, 1.0f);
}

inline const mat4 Frustum(float left, float right,
	float bottom, float top, float zNear, float zFar) {

	return mat4((2 * zNear) / (right - left), 0, (right + left) / (right - left), 0,
	            0, (2 * zNear) / (top - bottom), (top + bottom) / (top - bottom), 0,
	            0, 0, -(zFar + zNear) / (zFar - zNear), -(2 * zFar * zNear) / (zFar - zNear),
	            0, 0, -1, 0);
}

#endif // GRAPHICS_H