#ifndef VECTOR_2_H
#define VECTOR_2_H

template <class T>
class Vector_2;
typedef Vector_2<int>		vec2i;
typedef Vector_2<float>		vec2;
typedef Vector_2<double>	vec2d;
typedef Vector_2<unsigned int>	vec2ui;

#include "vector_3.h"
#include "vector_4.h"



//*************************************************************************************************
//Класс:	Vector_2
//Описание:	Обработка векторов типа (x,y) {
//*************************************************************************************************
template <typename T>
class Vector_2 {

public:

	T x;
	T y;

	// ~~~~~~~~~~~~~~~~
	//
	// ~~~~~~~~~~~~~~~~

	// Vector_2()
	Vector_2<T>() {
		this->x = 0;
		this->y = 0;
	}
	// Vector_2(T)
	Vector_2<T>(const T &Value1) {
		this->x = Value1;
		this->y = Value1;
	}
	// Vector_2(T, T)
	Vector_2<T>(const T &Value1, const T &Value2) {
		this->x = Value1;
		this->y = Value2;
	}
	// Vector_2(Vector_2<T>) {
	Vector_2(const Vector_2<T> &Value1) {

		this->x = Value1.x;
		this->y = Value1.y;
	}
	// Vector_2(Vector_3<T>) {
	Vector_2<T>(const Vector_3<T> &Value1) {
		this->x = Value1.x;
		this->y = Value1.y;
	}
	// Vector_2(Vector_4<T>) {
	Vector_2<T>(const Vector_4<T> &Value1) {
		this->x = Value1.x;
		this->y = Value1.y;
	}
	// Vector_2.normalize
	void normalize(void) {
		if (this->x == 0 && this->y == 0) return;
		Vector_2 _normVector(this->x, this->y);
		_normVector = _normVector / lenght(_normVector);
		this->x = _normVector.x;
		this->y = _normVector.y;
	}
	// Vector_2++
	const void operator++ (int) {
		this->x++;
		this->y++;
	};
	// Vector_2--
	const void operator-- (int) {
		this->x--;
		this->y--;
	};

	// ~~~~~~~~~~~~~~~~
	// ~~~~~~~~~~~~~~~~

	// Vector_2<T> += T
	const void operator+= (const T& rValue) {
		this->x += rValue;
		this->y += rValue;
	};
	// Vector_2<T> -= T
	const void operator-= (const T& rValue) {
		this->x -= rValue;
		this->y -= rValue;
	};
	// Vector_2<T> *= T
	const void operator*= (const T& rValue) {
		this->x *= rValue;
		this->y *= rValue;
	};
	// Vector_2<T> /= T
	const void operator/= (const T& rValue) {
		this->x /= rValue;
		this->y /= rValue;
	};
	// Vector_2<T> + T
	const Vector_2<T> operator+ (const T& rValue) {
		return Vector_2<T>(
			this->x + rValue,
			this->y + rValue);
	};
	// Vector_2<T> + T
	const Vector_2<T> operator+ (const T& rValue) const {
		return Vector_2<T>(
			this->x + rValue,
			this->y + rValue);
	};
	// Vector_2<T> - T
	const Vector_2<T> operator- (const T& rValue) {
		return Vector_2<T>(
			this->x - rValue,
			this->y - rValue);
	};
	// Vector_2<T> - T
	const Vector_2<T> operator- (const T& rValue) const {
		return Vector_2<T>(
			this->x - rValue,
			this->y - rValue);
	};
	// Vector_2<T> * T
	const Vector_2<T> operator* (const T& rValue) {
		return Vector_2<T>(
			this->x * rValue,
			this->y * rValue);
	};
	// Vector_2<T> * T
	const Vector_2<T> operator* (const T& rValue) const {
		return Vector_2<T>(
			this->x * rValue,
			this->y * rValue);
	};
	// Vector_2<T> / T
	const Vector_2<T> operator/ (const T& rValue) {
		return Vector_2<T>(
			this->x / rValue,
			this->y / rValue);
	};
	// Vector_2<T> / T
	const Vector_2<T> operator/ (const T& rValue) const {
		return Vector_2<T>(
			this->x / rValue,
			this->y / rValue);
	};
	// Vector_2<T> = T
	void operator= (const T& rValue) {
		this->x = rValue;
		this->y = rValue;
	};

	// ~~~~~~~~~~~~~~~~
	// Vector_2<T>
	// ~~~~~~~~~~~~~~~~

	// Vector_2<T> += Vector_2<T>
	const void operator+= (const Vector_2<T>& rValue) {
		this->x += rValue.x;
		this->y += rValue.y;
	};
	// Vector_2<T> -= Vector_2<T>
	const void operator-= (const Vector_2<T>& rValue) {
		this->x -= rValue.x;
		this->y -= rValue.y;
	};
	// Vector_2<T> *= Vector_2<T>
	const void operator*= (const Vector_2<T>& rValue) {
		this->x *= rValue.x;
		this->y *= rValue.y;
	};
	// Vector_2<T> /= Vector_2<T>
	const void operator/= (const Vector_2<T>& rValue) {
		this->x /= rValue.x;
		this->y /= rValue.y;
	};
	// Vector_2<T> + Vector_2<T>
	const Vector_2<T> operator+ (const Vector_2<T> &rValue) {
		return Vector_2<T>(
			this->x + rValue.x,
			this->y + rValue.y);
	};
	// Vector_2<T> + Vector_2<T>
	const Vector_2<T> operator+ (const Vector_2<T> &rValue) const {
		return Vector_2<T>(
			this->x + rValue.x,
			this->y + rValue.y);
	};
	// Vector_2<T> - Vector_2<T>
	const Vector_2<T> operator- (const Vector_2<T> &rValue) {
		return Vector_2<T>(
			this->x - rValue.x,
			this->y - rValue.y);
	};
	// Vector_2<T> - Vector_2<T>
	const Vector_2<T> operator- (const Vector_2<T> &rValue) const {
		return Vector_2<T>(
			this->x - rValue.x,
			this->y - rValue.y);
	};
	// Vector_2<T> * Vector_2<T>
	const Vector_2<T> operator* (const Vector_2<T> &rValue) {
		return Vector_2<T>(
			this->x * rValue.x,
			this->y * rValue.y);
	};
	// Vector_2<T> * Vector_2<T>
	const Vector_2<T> operator* (const Vector_2<T> &rValue) const {
		return Vector_2<T>(
			this->x * rValue.x,
			this->y * rValue.y);
	};
	// Vector_2<T> / Vector_2<T>
	const Vector_2<T> operator/ (const Vector_2<T> &rValue) {
		return Vector_2<T>(
			this->x / rValue.x,
			this->y / rValue.y);
	};
	// Vector_2<T> / Vector_2<T>
	const Vector_2<T> operator/ (const Vector_2<T> &rValue) const {
		return Vector_2<T>(
			this->x / rValue.x,
			this->y / rValue.y);
	};
	// Vector_2<T> = Vector_2<T>
	void operator= (const Vector_2<T> &rValue) {
		this->x = rValue.x;
		this->y = rValue.y;
	};

	// ~~~~~~~~~~~~~~~~
	// Vector_3<T>
	// ~~~~~~~~~~~~~~~~

	// Vector_2<T> += Vector_3<T>
	const void operator+= (const Vector_3<T>& rValue) {
		this->x += rValue.x;
		this->y += rValue.y;
	};
	// Vector_2<T> -= Vector_3<T>
	const void operator-= (const Vector_3<T>& rValue) {
		this->x -= rValue.x;
		this->y -= rValue.y;
	};
	// Vector_2<T> *= Vector_3<T>
	const void operator*= (const Vector_3<T>& rValue) {
		this->x *= rValue.x;
		this->y *= rValue.y;
	};
	// Vector_2<T> /= Vector_3<T>
	const void operator/= (const Vector_3<T>& rValue) {
		this->x /= rValue.x;
		this->y /= rValue.y;
	};
	// Vector_2<T> + Vector_3<T>
	const Vector_2<T> operator+ (const Vector_3<T> &rValue) {
		return Vector_2<T>(
			this->x + rValue.x,
			this->y + rValue.y);
	};
	// Vector_2<T> + Vector_3<T>
	const Vector_2<T> operator+ (const Vector_3<T> &rValue) const {
		return Vector_2<T>(
			this->x + rValue.x,
			this->y + rValue.y);
	};
	// Vector_2<T> - Vector_3<T>
	const Vector_2<T> operator- (const Vector_3<T> &rValue) {
		return Vector_2<T>(
			this->x - rValue.x,
			this->y - rValue.y);
	};
	// Vector_2<T> - Vector_3<T>
	const Vector_2<T> operator- (const Vector_3<T> &rValue) const {
		return Vector_2<T>(
			this->x - rValue.x,
			this->y - rValue.y);
	};
	// Vector_2<T> * Vector_3<T>
	const Vector_2<T> operator* (const Vector_3<T> &rValue) {
		return Vector_2<T>(
			this->x * rValue.x,
			this->y * rValue.y);
	};
	// Vector_2<T> * Vector_3<T>
	const Vector_2<T> operator* (const Vector_3<T> &rValue) const {
		return Vector_2<T>(
			this->x * rValue.x,
			this->y * rValue.y);
	};
	// Vector_2<T> / Vector_3<T>
	const Vector_2<T> operator/ (const Vector_3<T> &rValue) {
		return Vector_2<T>(
			this->x / rValue.x,
			this->y / rValue.y);
	};
	// Vector_2<T> / Vector_3<T>
	const Vector_2<T> operator/ (const Vector_3<T> &rValue) const {
		return Vector_2<T>(
			this->x / rValue.x,
			this->y / rValue.y);
	};
	// Vector_2<T> = Vector_3<T>
	void operator= (const Vector_3<T> &rValue) {
		this->x = rValue.x;
		this->y = rValue.y;
	};

	// ~~~~~~~~~~~~~~~~
	// Vector_4<T>
	// ~~~~~~~~~~~~~~~~

	// Vector_2<T> += Vector_4<T>
	const void operator+= (const Vector_4<T>& rValue) {
		this->x += rValue.x;
		this->y += rValue.y;
	};
	// Vector_2<T> -= Vector_4<T>
	const void operator-= (const Vector_4<T>& rValue) {
		this->x -= rValue.x;
		this->y -= rValue.y;
	};
	// Vector_2<T> *= Vector_4<T>
	const void operator*= (const Vector_4<T>& rValue) {
		this->x *= rValue.x;
		this->y *= rValue.y;
	};
	// Vector_2<T> /= Vector_4<T>
	const void operator/= (const Vector_4<T>& rValue) {
		this->x /= rValue.x;
		this->y /= rValue.y;
	};
	// Vector_2<T> + Vector_4<T>
	const Vector_3<T> operator+ (const Vector_4<T> &rValue) {
		return Vector_3<T>(
			this->x + rValue.x,
			this->y + rValue.y);
	};
	// Vector_2<T> + Vector_4<T>
	const Vector_3<T> operator+ (const Vector_4<T> &rValue) const {
		return Vector_3<T>(
			this->x + rValue.x,
			this->y + rValue.y);
	};
	// Vector_2<T> - Vector_4<T>
	const Vector_2<T> operator- (const Vector_4<T> &rValue) {
		return Vector_2<T>(
			this->x - rValue.x,
			this->y - rValue.y);
	};
	// Vector_2<T> - Vector_4<T>
	const Vector_2<T> operator- (const Vector_4<T> &rValue) const {
		return Vector_2<T>(
			this->x - rValue.x,
			this->y - rValue.y);
	};
	// Vector_2<T> * Vector_4<T>
	const Vector_2<T> operator* (const Vector_4<T> &rValue) {
		return Vector_2<T>(
			this->x * rValue.x,
			this->y * rValue.y);
	};
	// Vector_2<T> * Vector_4<T>
	const Vector_2<T> operator* (const Vector_4<T> &rValue) const {
		return Vector_2<T>(
			this->x * rValue.x,
			this->y * rValue.y);
	};
	// Vector_2<T> / Vector_4<T>
	const Vector_2<T> operator/ (const Vector_4<T> &rValue) {
		return Vector_2<T>(
			this->x / rValue.x,
			this->y / rValue.y);
	};
	// Vector_2<T> / Vector_4<T>
	const Vector_2<T> operator/ (const Vector_4<T> &rValue) const {
		return Vector_2<T>(
			this->x / rValue.x,
			this->y / rValue.y);
	};
	// Vector_2<T> = Vector_4<T>
	void operator= (const Vector_4<T> &rValue) {
		this->x = rValue.x;
		this->y = rValue.y;
	};
};

template <typename T>
bool operator== (const Vector_2<T>& Value1, const Vector_2<T>& Value2) { 

	return Value1.x == Value2.x && Value1.y == Value2.y ? true : false;

}

template <typename T>
bool operator!= (const Vector_2<T>& Value1, const Vector_2<T>& Value2) { 

	return Value1.x != Value2.x || Value1.y != Value2.y ? true : false;
}

/// скалярное произведение
template <typename T>
T dot(const Vector_2<T>& Value1, const Vector_2<T>& Value2) { 
		return Value1.x * Value2.x + Value1.y * Value2.y;
}
/// длина вектора
template <typename T>
T lenght(const Vector_2<T>& Value1) { 
		long double _dot = dot(Value1, Value1);
		return (T) sqrt(_dot);
}
/// нормализация вектора
template <typename T>
Vector_2<T> normalize(const Vector_2<T>& Value1) { 
	if (Value1.x == 0 && Value1.y == 0) { 
		return Vector_2<T>(Value1);
	}
	
	return Vector_2<T>(Value1 / lenght(Value1));
}

#endif // VECTOR_2_H