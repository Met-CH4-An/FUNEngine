#ifndef VECTOR_4_H
#define VECTOR_4_H

template <class T>
class Vector_4;
typedef Vector_4<int>		vec4i;
typedef Vector_4<float>		vec4;
typedef Vector_4<double>	vec4d;

#include "vector_2.h"
#include "vector_3.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*!	\brief Буфер для данных.
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <typename T>
class Vector_4 {
public:

	T x;
	T y;
	T z;
	T w;

	// ~~~~~~~~~~~~~~~~
	//
	// ~~~~~~~~~~~~~~~~

	// Vector_4()
	Vector_4<T>() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}
	// Vector_4(T)
	Vector_4<T>(const T &Value1) {
		this->x = Value1;
		this->y = Value1;
		this->z = Value1;
		this->w = Value1;
	}
	// Vector_4(T, T, T, T)
	Vector_4<T>(const T &Value1, const T &Value2, const T &Value3, const T &Value4) {
		this->x = Value1;
		this->y = Value2;
		this->z = Value3;
		this->w = Value4;
	}
	// Vector_4(Vector_2<T>) {
	Vector_4(const Vector_2<T> &Value1) {
			
		this->x = Value1.x;
		this->y = Value1.y;
		this->z = 0;
		this->w = 0;
	}
	// Vector_4(Vector_2<T>, T) {
	Vector_4<T>(const Vector_2<T> &Value1, const T &Value2) {
		this->x = Value1.x;
		this->y = Value1.y;
		this->z = Value2;
		this->w = 0;
	}
	// Vector_4(Vector_2<T>, T, T) {
	Vector_4<T>(const Vector_2<T> &Value1, const T &Value2, const T &Value3) {
		this->x = Value1.x;
		this->y = Value1.y;
		this->z = Value2;
		this->w = Value3;
	}
	// Vector_4(Vector_3<T>) {
	Vector_4<T>(const Vector_3<T> &Value1) {
		this->x = Value1.x;
		this->y = Value1.y;
		this->z = Value1.z;
		this->w = 0;
	}
	// Vector_4(Vector_3<T>, T) {
	Vector_4<T>(const Vector_3<T> &Value1, const T &Value2) {
		this->x = Value1.x;
		this->y = Value1.y;
		this->z = Value1.z;
		this->w = Value2;
	}
	// Vector_4(Vector_4<T>) {
	Vector_4<T>(const Vector_4<T> &Value1) {
		this->x = Value1.x;
		this->y = Value1.y;
		this->z = Value1.z;
		this->w = Value1.w;
	}
	// Vector_4.normalize
	void normalize(void) {
		if(this->x == 0 && this->y == 0 && this->z == 0 && this->w == 0) return;
		Vector_4 _normVector(this->x, this->y, this->z, this->w);
		_normVector = _normVector / lenght(_normVector);
		this->x = _normVector.x;
		this->y = _normVector.y;
		this->z = _normVector.z;
		this->w = _normVector.w;
	}
	// Vector_4++
	const void operator++ (int) {
		this->x++;
		this->y++;
		this->z++;
		this->w++;
	};
	// Vector_4--
	const void operator-- (int) {
		this->x--;
		this->y--;
		this->z--;
		this->w--;
	};

	// ~~~~~~~~~~~~~~~~
	// ~~~~~~~~~~~~~~~~

	// Vector_4<T> += T
	const void operator+= (const T& rValue) {
		this->x += rValue;
		this->y += rValue;
		this->z += rValue;
		this->w += rValue;
	};
	// Vector_4<T> -= T
	const void operator-= (const T& rValue) {
		this->x -= rValue;
		this->y -= rValue;
		this->z -= rValue;
		this->w -= rValue;
	};
	// Vector_4<T> *= T
	const void operator*= (const T& rValue) {
		this->x *= rValue;
		this->y *= rValue;
		this->z *= rValue;
		this->w *= rValue;
	};
	// Vector_4<T> /= T
	const void operator/= (const T& rValue) {
		this->x /= rValue;
		this->y /= rValue;
		this->z /= rValue;
		this->w /= rValue;
	};
	// Vector_4<T> + T
	const Vector_4<T> operator+ (const T& rValue) {
		return Vector_4<T>(
			this->x + rValue,
			this->y + rValue,
			this->z + rValue,
			this->w + rValue);
	};
	// Vector_4<T> + T
	const Vector_4<T> operator+ (const T& rValue) const {
		return Vector_4<T>(
			this->x + rValue,
			this->y + rValue,
			this->z + rValue,
			this->w + rValue);
	};
	// Vector_4<T> - T
	const Vector_4<T> operator- (const T& rValue) {
		return Vector_4<T>(
			this->x - rValue,
			this->y - rValue,
			this->z - rValue,
			this->w - rValue);
	};
	// Vector_4<T> - T
	const Vector_4<T> operator- (const T& rValue) const {
		return Vector_4<T>(
			this->x - rValue,
			this->y - rValue,
			this->z - rValue,
			this->w - rValue);
	};
	// Vector_4<T> * T
	const Vector_4<T> operator* (const T& rValue) {
		return Vector_4<T>(
			this->x * rValue,
			this->y * rValue,
			this->z * rValue,
			this->w * rValue);
	};
	// Vector_4<T> * T
	const Vector_4<T> operator* (const T& rValue) const {
		return Vector_4<T>(
			this->x * rValue,
			this->y * rValue,
			this->z * rValue,
			this->w * rValue);
	};
	// Vector_4<T> / T
	const Vector_4<T> operator/ (const T& rValue) {
		return Vector_4<T>(
			this->x / rValue,
			this->y / rValue,
			this->z / rValue,
			this->w / rValue);
	};
	// Vector_4<T> / T
	const Vector_4<T> operator/ (const T& rValue) const {
		return Vector_4<T>(
			this->x / rValue,
			this->y / rValue,
			this->z / rValue,
			this->w / rValue);
	};
	// vec4 = T
	void operator= (const T& rValue) {
		this->x = rValue;
		this->y = rValue;
		this->z = rValue;
		this->w = rValue;
	};

	// ~~~~~~~~~~~~~~~~
	// ~~~~~~~~~~~~~~~~

	// Vector_4<T> += Vector_2<T>
	const void operator+= (const Vector_2<T>& rValue) {
		this->x += rValue.x;
		this->y += rValue.y;
	};
	// Vector_4<T> -= Vector_2<T>
	const void operator-= (const Vector_2<T>& rValue) {
		this->x -= rValue.x;
		this->y -= rValue.y;
	};
	// Vector_4<T> *= Vector_2<T>
	const void operator*= (const Vector_2<T>& rValue) {
		this->x *= rValue.x;
		this->y *= rValue.y;
	};
	// Vector_4<T> /= Vector_2<T>
	const void operator/= (const Vector_2<T>& rValue) {
		this->x /= rValue.x;
		this->y /= rValue.y;
	};
	// Vector_4<T> + Vector_2<T>
	const Vector_4<T> operator+ (const Vector_2<T> &rValue) {
		return Vector_4<T>(this->x + rValue.x,
			this->y + rValue.y,
			this->z,
			this->w);
	};
	// Vector_4<T> + Vector_2<T>
	const Vector_4<T> operator+ (const Vector_2<T> &rValue) const {
		return Vector_4<T>(this->x + rValue.x,
			this->y + rValue.y,
			this->z,
			this->w);
	};
	// Vector_4<T> - Vector_2<T>
	const Vector_4<T> operator- (const Vector_2<T> &rValue) {
		return Vector_4<T>(this->x - rValue.x,
			this->y - rValue.y,
			this->z,
			this->w);
	};
	// Vector_4<T> - Vector_2<T>
	const Vector_4<T> operator- (const Vector_2<T> &rValue) const {
		return Vector_4<T>(this->x - rValue.x,
			this->y - rValue.y,
			this->z,
			this->w);
	};
	// Vector_4<T> * Vector_2<T>
	const Vector_4<T> operator* (const Vector_2<T> &rValue) {
		return Vector_4<T>(this->x * rValue.x,
			this->y * rValue.y,
			this->z,
			this->w);
	};
	// Vector_4<T> * Vector_2<T>
	const Vector_4<T> operator* (const Vector_2<T> &rValue) const {
		return Vector_4<T>(this->x * rValue.x,
			this->y * rValue.y,
			this->z,
			this->w);
	};
	// Vector_4<T> / Vector_2<T>
	const Vector_4<T> operator/ (const Vector_2<T> &rValue) {
		return Vector_4<T>(this->x / rValue.x,
			this->y / rValue.y,
			this->z,
			this->w);
	};
	// Vector_4<T> / Vector_2<T>
	const Vector_4<T> operator/ (const Vector_2<T> &rValue) const {
		return Vector_4<T>(this->x / rValue.x,
			this->y / rValue.y,
			this->z,
			this->w);
	};
	// Vector_4<T> = Vector_2<T>
	void operator= (const Vector_2<T> &rValue) {
		this->x = rValue.x;
		this->y = rValue.y;
	};

	// ~~~~~~~~~~~~~~~~
	// Vector_3<T>
	// ~~~~~~~~~~~~~~~~

	// Vector_4<T> += Vector_3<T>
	const void operator+= (const Vector_3<T>& rValue) {
		this->x += rValue.x;
		this->y += rValue.y;
		this->z += rValue.z;
	};
	// Vector_4<T> -= Vector_3<T>
	const void operator-= (const Vector_3<T>& rValue) {
		this->x -= rValue.x;
		this->y -= rValue.y;
		this->z -= rValue.z;
	};
	// Vector_4<T> *= Vector_3<T>
	const void operator*= (const Vector_3<T>& rValue) {
		this->x *= rValue.x;
		this->y *= rValue.y;
		this->z *= rValue.z;
	};
	// Vector_4<T> /= Vector_3<T>
	const void operator/= (const Vector_3<T>& rValue) {
		this->x /= rValue.x;
		this->y /= rValue.y;
		this->z /= rValue.z;
	};
	// Vector_4<T> + Vector_3<T>
	const Vector_4<T> operator+ (const Vector_3<T> &rValue) {
		return Vector_4<T>(
			this->x + rValue.x,
			this->y + rValue.y,
			this->z + rValue.z,
			this->w);
	};
	// Vector_4<T> + Vector_3<T>
	const Vector_4<T> operator+ (const Vector_3<T> &rValue) const {
		return Vector_4<T>(
			this->x + rValue.x,
			this->y + rValue.y,
			this->z + rValue.z,
			this->w);
	};
	// Vector_4<T> - Vector_3<T>
	const Vector_4<T> operator- (const Vector_3<T> &rValue) {
		return Vector_4<T>(
			this->x - rValue.x,
			this->y - rValue.y,
			this->z - rValue.z);
	};
	// Vector_4<T> - Vector_3<T>
	const Vector_4<T> operator- (const Vector_3<T> &rValue) const {
		return Vector_4<T>(
			this->x - rValue.x,
			this->y - rValue.y,
			this->z - rValue.z);
	};
	// Vector_4<T> * Vector_3<T>
	const Vector_4<T> operator* (const Vector_3<T> &rValue) {
		return Vector_4<T>(
			this->x * rValue.x,
			this->y * rValue.y,
			this->z * rValue.z);
	};
	// Vector_4<T> * Vector_3<T>
	const Vector_4<T> operator* (const Vector_3<T> &rValue) const {
		return Vector_4<T>(
			this->x * rValue.x,
			this->y * rValue.y,
			this->z * rValue.z);
	};
	// Vector_4<T> / Vector_3<T>
	const Vector_4<T> operator/ (const Vector_3<T> &rValue) {
		return Vector_4<T>(
			this->x / rValue.x,
			this->y / rValue.y,
			this->z / rValue.z);
	};
	// Vector_4<T> / Vector_3<T>
	const Vector_4<T> operator/ (const Vector_3<T> &rValue) const {
		return Vector_4<T>(
			this->x / rValue.x,
			this->y / rValue.y,
			this->z / rValue.z);
	};
	// Vector_4<T> = Vector_3<T>
	void operator= (const Vector_3<T> &rValue) {
		this->x = rValue.x;
		this->y = rValue.y;
		this->z = rValue.z;
	};

	// ~~~~~~~~~~~~~~~~
	// ~~~~~~~~~~~~~~~~

	// Vector_4<T> += Vector_4<T>
	const void operator+= (const Vector_4<T>& rValue) {
		this->x += rValue.x;
		this->y += rValue.y;
		this->z += rValue.z;
		this->w += rValue.w;
	};
	// Vector_4<T> -= Vector_4<T>
	const void operator-= (const Vector_4<T>& rValue) {
		this->x -= rValue.x;
		this->y -= rValue.y;
		this->z -= rValue.z;
		this->w -= rValue.w;
	};
	// Vector_4<T> *= Vector_4<T>
	const void operator*= (const Vector_4<T>& rValue) {
		this->x *= rValue.x;
		this->y *= rValue.y;
		this->z *= rValue.z;
		this->w *= rValue.w;
	};
	// Vector_4<T> /= Vector_4<T>
	const void operator/= (const Vector_4<T>& rValue) {
		this->x /= rValue.x;
		this->y /= rValue.y;
		this->z /= rValue.z;
		this->w /= rValue.w;
	};
	// Vector_4<T> + Vector_4<T>
	const Vector_4<T> operator+ (const Vector_4<T> &rValue) {
		return Vector_4<T>(
			this->x + rValue.x,
			this->y + rValue.y,
			this->z + rValue.z,
			this->w + rValue.w);
	};
	// Vector_4<T> + Vector_4<T>
	const Vector_4<T> operator+ (const Vector_4<T> &rValue) const {
		return Vector_4<T>(
			this->x + rValue.x,
			this->y + rValue.y,
			this->z + rValue.z,
			this->w + rValue.w);
	};
	// Vector_4<T> - Vector_4<T>
	const Vector_4<T> operator- (const Vector_4<T> &rValue) {
		return Vector_4<T>(
			this->x - rValue.x,
			this->y - rValue.y,
			this->z - rValue.z,
			this->w - rValue.w);
	};
	// Vector_4<T> - Vector_4<T>
	const Vector_4<T> operator- (const Vector_4<T> &rValue) const {
		return Vector_4<T>(
			this->x - rValue.x,
			this->y - rValue.y,
			this->z - rValue.z,
			this->w - rValue.w);
	};
	// Vector_4<T> * Vector_4<T>
	const Vector_4<T> operator* (const Vector_4<T> &rValue) {
		return Vector_4<T>(
			this->x * rValue.x,
			this->y * rValue.y,
			this->z * rValue.z,
			this->w * rValue.w);
	};
	// Vector_4<T> * Vector_4<T>
	const Vector_4<T> operator* (const Vector_4<T> &rValue) const {
		return Vector_4<T>(
			this->x * rValue.x,
			this->y * rValue.y,
			this->z * rValue.z,
			this->w * rValue.w);
	};
	// Vector_4<T> / Vector_4<T>
	const Vector_4<T> operator/ (const Vector_4<T> &rValue) {
		return Vector_4<T>(
			this->x / rValue.x,
			this->y / rValue.y,
			this->z / rValue.z,
			this->w / rValue.w);
	};
	// Vector_4<T> / Vector_4<T>
	const Vector_4<T> operator/ (const Vector_4<T> &rValue) const {
		return Vector_4<T>(
			this->x / rValue.x,
			this->y / rValue.y,
			this->z / rValue.z,
			this->w / rValue.w);
	};
	// Vector_4<T> = Vector_4<T>
	void operator= (const Vector_4<T> &rValue) {
		this->x = rValue.x;
		this->y = rValue.y;
		this->z = rValue.z;
	};
};
/// скалярное произведение
template<class T>
T dot(const Vector_4<T>& Value1, const Vector_4<T>& Value2) { 
		return Value1.x * Value2.x + Value1.y * Value2.y + Value1.z * Value2.z + Value1.w * Value2.w;
}
/// длина вектора
template<class T>
T lenght(const Vector_4<T>& Value1) { 
		long double _dot = dot(Value1, Value1);
		return (T) sqrt(_dot);
}
/// нормализация вектора
template<class T>
Vector_4<T> normalize(const Vector_4<T>& Value1) { 
	if (Value1.x == 0 && Value1.y == 0 && Value1.z == 0 && Value1.w == 0) { return Vector_4<T>(Value1); }
		return Vector_4<T>(Value1 / lenght(Value1) );
}
// vector == vector
template<class T>
const bool operator== (const Vector_4<T>& Value1, const Vector_4<T>& Value2) {

	return Value1.x == Value2.x && Value1.y == Value2.y && Value1.z == Value2.z && Value1.w == Value2.w;
	
}

#endif // VECTOR_4_H