#ifndef VECTOR_3_H
#define VECTOR_3_H

#include <stdint.h>

template <class T>
class Vector_3;
typedef Vector_3<int>		vec3i;
typedef Vector_3<float>		vec3;
typedef Vector_3<double>	vec3d;
#include "vector_2.h"
#include "vector_4.h"

//*************************************************************************************************
//Класс:	Vector_3
//Описание:	Обработка векторов типа (x,y,z) {
//*************************************************************************************************
template <class T>
class Vector_3 {

public:

	T x;
	T y;
	T z;

	// ~~~~~~~~~~~~~~~~
	//
	// ~~~~~~~~~~~~~~~~

	// Vector_3()
	Vector_3<T>() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	// Vector_3(T)
	Vector_3<T>(const T &Value1) {
		this->x = Value1;
		this->y = Value1;
		this->z = Value1;
	}
	// Vector_3(T, T, T)
	Vector_3<T>(const T &Value1, const T &Value2, const T &Value3) {
		this->x = Value1;
		this->y = Value2;
		this->z = Value3;
	}
	// Vector_3(Vector_2<T>) {
	Vector_3(const Vector_2<T> &Value1) {

		this->x = Value1.x;
		this->y = Value1.y;
		this->z = 0;
	}
	// Vector_3(Vector_2<T>, T) {
	Vector_3<T>(const Vector_2<T> &Value1, const T &Value2) {
		this->x = Value1.x;
		this->y = Value1.y;
		this->z = Value2;
	}
	// Vector_3(Vector_3<T>) {
	Vector_3<T>(const Vector_3<T> &Value1) {
		this->x = Value1.x;
		this->y = Value1.y;
		this->z = Value1.z;
	}
	// Vector_3(Vector_4<T>) {
	Vector_3<T>(const Vector_4<T> &Value1) {
		this->x = Value1.x;
		this->y = Value1.y;
		this->z = Value1.z;
	}
	// Vector_3.normalize
	void normalize(void) {
		if (this->x == 0 && this->y == 0 && this->z == 0) return;
		Vector_3 _normVector(this->x, this->y, this->z);
		_normVector = _normVector / lenght(_normVector);
		this->x = _normVector.x;
		this->y = _normVector.y;
		this->z = _normVector.z;
	}
	// Vector_3++
	const void operator++ (int) {
		this->x++;
		this->y++;
		this->z++;
	};
	// Vector_3--
	const void operator-- (int) {
		this->x--;
		this->y--;
		this->z--;
	};

	// ~~~~~~~~~~~~~~~~
	// ~~~~~~~~~~~~~~~~

	// Vector_3<T> += T
	const void operator+= (const T& rValue) {
		this->x += rValue;
		this->y += rValue;
		this->z += rValue;
	};
	// Vector_3<T> -= T
	const void operator-= (const T& rValue) {
		this->x -= rValue;
		this->y -= rValue;
		this->z -= rValue;
	};
	// Vector_3<T> *= T
	const void operator*= (const T& rValue) {
		this->x *= rValue;
		this->y *= rValue;
		this->z *= rValue;
	};
	// Vector_3<T> /= T
	const void operator/= (const T& rValue) {
		this->x /= rValue;
		this->y /= rValue;
		this->z /= rValue;
	};
	// Vector_3<T> + T
	const Vector_3<T> operator+ (const T& rValue) {
		return Vector_3<T>(
			this->x + rValue,
			this->y + rValue,
			this->z + rValue);
	};
	// Vector_3<T> + T
	const Vector_3<T> operator+ (const T& rValue) const {
		return Vector_3<T>(
			this->x + rValue,
			this->y + rValue,
			this->z + rValue);
	};
	// Vector_3<T> - T
	const Vector_3<T> operator- (const T& rValue) {
		return Vector_3<T>(
			this->x - rValue,
			this->y - rValue,
			this->z - rValue);
	};
	// Vector_3<T> - T
	const Vector_3<T> operator- (const T& rValue) const {
		return Vector_3<T>(
			this->x - rValue,
			this->y - rValue,
			this->z - rValue);
	};
	// Vector_3<T> * T
	const Vector_3<T> operator* (const T& rValue) {
		return Vector_3<T>(
			this->x * rValue,
			this->y * rValue,
			this->z * rValue);
	};
	// Vector_3<T> * T
	const Vector_3<T> operator* (const T& rValue) const {
		return Vector_3<T>(
			this->x * rValue,
			this->y * rValue,
			this->z * rValue);
	};
	// Vector_3<T> / T
	const Vector_3<T> operator/ (const T& rValue) {
		return Vector_3<T>(
			this->x / rValue,
			this->y / rValue,
			this->z / rValue);
	};
	// Vector_3<T> / T
	const Vector_3<T> operator/ (const T& rValue) const {
		return Vector_3<T>(
			this->x / rValue,
			this->y / rValue,
			this->z / rValue);
	};
	// vec4 = T
	void operator= (const T& rValue) {
		this->x = rValue;
		this->y = rValue;
		this->z = rValue;
	};

	// ~~~~~~~~~~~~~~~~
	// Vector_2<T>
	// ~~~~~~~~~~~~~~~~

	// Vector_3<T> += Vector_2<T>
	const void operator+= (const Vector_2<T>& rValue) {
		this->x += rValue.x;
		this->y += rValue.y;
	};
	// Vector_3<T> -= Vector_2<T>
	const void operator-= (const Vector_2<T>& rValue) {
		this->x -= rValue.x;
		this->y -= rValue.y;
	};
	// Vector_3<T> *= Vector_2<T>
	const void operator*= (const Vector_2<T>& rValue) {
		this->x *= rValue.x;
		this->y *= rValue.y;
	};
	// Vector_3<T> /= Vector_2<T>
	const void operator/= (const Vector_2<T>& rValue) {
		this->x /= rValue.x;
		this->y /= rValue.y;
	};
	// Vector_3<T> + Vector_2<T>
	const Vector_3<T> operator+ (const Vector_2<T> &rValue) {
		return Vector_3<T>(
			this->x + rValue.x,
			this->y + rValue.y,
			this->z,
			this->w);
	};
	// Vector_3<T> + Vector_2<T>
	const Vector_3<T> operator+ (const Vector_2<T> &rValue) const {
		return Vector_3<T>(
			this->x + rValue.x,
			this->y + rValue.y,
			this->z,
			this->w);
	};
	// Vector_3<T> - Vector_2<T>
	const Vector_3<T> operator- (const Vector_2<T> &rValue) {
		return Vector_3<T>(
			this->x - rValue.x,
			this->y - rValue.y,
			this->z,
			this->w);
	};
	// Vector_3<T> - Vector_2<T>
	const Vector_3<T> operator- (const Vector_2<T> &rValue) const {
		return Vector_3<T>(
			this->x - rValue.x,
			this->y - rValue.y,
			this->z,
			this->w);
	};
	// Vector_3<T> * Vector_2<T>
	const Vector_3<T> operator* (const Vector_2<T> &rValue) {
		return Vector_3<T>(
			this->x * rValue.x,
			this->y * rValue.y,
			this->z,
			this->w);
	};
	// Vector_3<T> * Vector_2<T>
	const Vector_3<T> operator* (const Vector_2<T> &rValue) const {
		return Vector_3<T>(
			this->x * rValue.x,
			this->y * rValue.y,
			this->z,
			this->w);
	};
	// Vector_3<T> / Vector_2<T>
	const Vector_3<T> operator/ (const Vector_2<T> &rValue) {
		return Vector_3<T>(
			this->x / rValue.x,
			this->y / rValue.y,
			this->z,
			this->w);
	};
	// Vector_3<T> / Vector_2<T>
	const Vector_3<T> operator/ (const Vector_2<T> &rValue) const {
		return Vector_3<T>(
			this->x / rValue.x,
			this->y / rValue.y,
			this->z,
			this->w);
	};
	// Vector_3<T> = Vector_2<T>
	void operator= (const Vector_2<T> &rValue) {
		this->x = rValue.x;
		this->y = rValue.y;
	};

	// ~~~~~~~~~~~~~~~~
	// Vector_3<T>
	// ~~~~~~~~~~~~~~~~

	// Vector_3<T> += Vector_3<T>
	const void operator+= (const Vector_3<T>& rValue) {
		this->x += rValue.x;
		this->y += rValue.y;
		this->z += rValue.z;
	};
	// Vector_3<T> -= Vector_3<T>
	const void operator-= (const Vector_3<T>& rValue) {
		this->x -= rValue.x;
		this->y -= rValue.y;
		this->z -= rValue.z;
	};
	// Vector_3<T> *= Vector_3<T>
	const void operator*= (const Vector_3<T>& rValue) {
		this->x *= rValue.x;
		this->y *= rValue.y;
		this->z *= rValue.z;
	};
	// Vector_3<T> /= Vector_3<T>
	const void operator/= (const Vector_3<T>& rValue) {
		this->x /= rValue.x;
		this->y /= rValue.y;
		this->z /= rValue.z;
	};
	// Vector_3<T> + Vector_3<T>
	const Vector_3<T> operator+ (const Vector_3<T> &rValue) {
		return Vector_3<T>(
			this->x + rValue.x,
			this->y + rValue.y,
			this->z + rValue.z);
	};
	// Vector_3<T> + Vector_3<T>
	const Vector_3<T> operator+ (const Vector_3<T> &rValue) const {
		return Vector_3<T>(
			this->x + rValue.x,
			this->y + rValue.y,
			this->z + rValue.z);
	};
	// Vector_3<T> - Vector_3<T>
	const Vector_3<T> operator- (const Vector_3<T> &rValue) {
		return Vector_3<T>(
			this->x - rValue.x,
			this->y - rValue.y,
			this->z - rValue.z);
	};
	// Vector_3<T> - Vector_3<T>
	const Vector_3<T> operator- (const Vector_3<T> &rValue) const {
		return Vector_3<T>(
			this->x - rValue.x,
			this->y - rValue.y,
			this->z - rValue.z);
	};
	// Vector_3<T> * Vector_3<T>
	const Vector_3<T> operator* (const Vector_3<T> &rValue) {
		return Vector_3<T>(
			this->x * rValue.x,
			this->y * rValue.y,
			this->z * rValue.z);
	};
	// Vector_3<T> * Vector_3<T>
	const Vector_3<T> operator* (const Vector_3<T> &rValue) const {
		return Vector_3<T>(
			this->x * rValue.x,
			this->y * rValue.y,
			this->z * rValue.z);
	};
	// Vector_3<T> / Vector_3<T>
	const Vector_3<T> operator/ (const Vector_3<T> &rValue) {
		return Vector_3<T>(
			this->x / rValue.x,
			this->y / rValue.y,
			this->z / rValue.z);
	};
	// Vector_3<T> / Vector_3<T>
	const Vector_3<T> operator/ (const Vector_3<T> &rValue) const {
		return Vector_3<T>(
			this->x / rValue.x,
			this->y / rValue.y,
			this->z / rValue.z);
	};
	// Vector_3<T> = Vector_3<T>
	void operator= (const Vector_3<T> &rValue) {
		this->x = rValue.x;
		this->y = rValue.y;
		this->z = rValue.z;
	};

	// ~~~~~~~~~~~~~~~~
	// Vector_4<T>
	// ~~~~~~~~~~~~~~~~

	// Vector_3<T> += Vector_4<T>
	const void operator+= (const Vector_4<T>& rValue) {
		this->x += rValue.x;
		this->y += rValue.y;
		this->z += rValue.z;
	};
	// Vector_3<T> -= Vector_4<T>
	const void operator-= (const Vector_4<T>& rValue) {
		this->x -= rValue.x;
		this->y -= rValue.y;
		this->z -= rValue.z;
	};
	// Vector_3<T> *= Vector_4<T>
	const void operator*= (const Vector_4<T>& rValue) {
		this->x *= rValue.x;
		this->y *= rValue.y;
		this->z *= rValue.z;
	};
	// Vector_3<T> /= Vector_4<T>
	const void operator/= (const Vector_4<T>& rValue) {
		this->x /= rValue.x;
		this->y /= rValue.y;
		this->z /= rValue.z;
	};
	// Vector_3<T> + Vector_4<T>
	const Vector_3<T> operator+ (const Vector_4<T> &rValue) {
		return Vector_3<T>(
			this->x + rValue.x,
			this->y + rValue.y,
			this->z + rValue.z);
	};
	// Vector_3<T> + Vector_4<T>
	const Vector_3<T> operator+ (const Vector_4<T> &rValue) const {
		return Vector_3<T>(
			this->x + rValue.x,
			this->y + rValue.y,
			this->z + rValue.z);
	};
	// Vector_3<T> - Vector_4<T>
	const Vector_3<T> operator- (const Vector_4<T> &rValue) {
		return Vector_3<T>(
			this->x - rValue.x,
			this->y - rValue.y,
			this->z - rValue.z);
	};
	// Vector_3<T> - Vector_4<T>
	const Vector_3<T> operator- (const Vector_4<T> &rValue) const {
		return Vector_3<T>(
			this->x - rValue.x,
			this->y - rValue.y,
			this->z - rValue.z);
	};
	// Vector_3<T> * Vector_4<T>
	const Vector_3<T> operator* (const Vector_4<T> &rValue) {
		return Vector_3<T>(
			this->x * rValue.x,
			this->y * rValue.y,
			this->z * rValue.z);
	};
	// Vector_3<T> * Vector_4<T>
	const Vector_3<T> operator* (const Vector_4<T> &rValue) const {
		return Vector_3<T>(
			this->x * rValue.x,
			this->y * rValue.y,
			this->z * rValue.z);
	};
	// Vector_3<T> / Vector_4<T>
	const Vector_3<T> operator/ (const Vector_4<T> &rValue) {
		return Vector_3<T>(
			this->x / rValue.x,
			this->y / rValue.y,
			this->z / rValue.z);
	};
	// Vector_3<T> / Vector_4<T>
	const Vector_3<T> operator/ (const Vector_4<T> &rValue) const {
		return Vector_3<T>(
			this->x / rValue.x,
			this->y / rValue.y,
			this->z / rValue.z);
	};
	// Vector_3<T> = Vector_4<T>
	void operator= (const Vector_4<T> &rValue) {
		this->x = rValue.x;
		this->y = rValue.y;
		this->z = rValue.z;
	};

	T operator[] (uint32_t id) {
		if (id == 0) return x;
		if (id == 1) return y;
		if (id == 2) return z;
	}
	//uint32_t demension(void) const { return 3; }
};
/// векторное произведение
template<class T>
Vector_3<T> cross(const Vector_3<T>& Value1, const Vector_3<T>& Value2) { 
		return Vector_3<T>(	Value1.y*Value2.z - Value1.z*Value2.y,
							Value1.z*Value2.x - Value1.x*Value2.z,
							Value1.x*Value2.y - Value1.y*Value2.x);
}
/// скалярное произведение
template<class T>
T dot(const Vector_3<T>& Value1, const Vector_3<T>& Value2) { 
		return Value1.x * Value2.x + Value1.y * Value2.y + Value1.z * Value2.z;
}
/// длина вектора
template<class T>
T lenght(const Vector_3<T>& Value1) { 
		long double _dot = dot(Value1, Value1);
		return (T) sqrt(_dot);

}
/// нормализация вектора
template<class T>
Vector_3<T> normalize(const Vector_3<T>& Value1) { 
	if (Value1.x == 0 && Value1.y == 0 && Value1.z == 0) { return Vector_3<T>(Value1); }
		return Vector_3<T>(Value1 / lenght(Value1));
}

#endif // VECTOR_3_H


