#ifndef MATRIX_3X3_H
#define MATRIX_3X3_H

#include "math.h"

template <class T>
class Matrix_3x3;

#include "matrix_4x4.h"
#include "vector_2.h"
#include "vector_3.h"
#include "vector_4.h"

typedef Matrix_3x3<int>		mat3i;
typedef Matrix_3x3<float>	mat3;
typedef Matrix_3x3<double>	mat3d;

//*************************************************************************************************
//Класс:	Matrix_3x3
//Описание:	Обработка матриц 3 на 3
//*************************************************************************************************
template <typename T>
class Matrix_3x3 {

public:
	T m[9];

	Matrix_3x3() {
		this->m[0] = 1;		this->m[1] = 0;		this->m[2] = 0;
		this->m[3] = 0;		this->m[4] = 1;		this->m[5] = 0;
		this->m[6] = 0;		this->m[7] = 0;		this->m[8] = 1;
	}

	Matrix_3x3(	const T &Value1,	const T &Value2,	const T &Value3,
				const T &Value4,	const T &Value5,	const T &Value6,
				const T &Value7,	const T &Value8,	const T &Value9) {
		this->m[0] = Value1;		this->m[1] = Value2;		this->m[2] = Value3;
		this->m[3] = Value4;		this->m[4] = Value5;		this->m[5] = Value6;
		this->m[6] = Value7;		this->m[7] = Value8;		this->m[8] = Value9;
	}

	Matrix_3x3(const Matrix_3x3<double> &Value1) {
		this->m[ 0] = Value1.m[ 0];	this->m[ 1] = Value1.m[1];	this->m[ 2] = Value1.m[ 2];
		this->m[ 3] = Value1.m[ 3];	this->m[ 4] = Value1.m[4];	this->m[ 5] = Value1.m[ 5];
		this->m[ 6] = Value1.m[ 6];	this->m[ 7] = Value1.m[7];	this->m[ 8] = Value1.m[ 8];
	}

	Matrix_3x3(const Matrix_3x3<float> &Value1) {
		this->m[ 0] = Value1.m[ 0];	this->m[ 1] = Value1.m[1];	this->m[ 2] = Value1.m[ 2];
		this->m[ 3] = Value1.m[ 3];	this->m[ 4] = Value1.m[4];	this->m[ 5] = Value1.m[ 5];
		this->m[ 6] = Value1.m[ 6];	this->m[ 7] = Value1.m[7];	this->m[ 8] = Value1.m[ 8];
	}

	Matrix_3x3(const Matrix_3x3<int> &Value1) {
		this->m[ 0] = Value1.m[ 0];	this->m[ 1] = Value1.m[1];	this->m[ 2] = Value1.m[ 2];
		this->m[ 3] = Value1.m[ 3];	this->m[ 4] = Value1.m[4];	this->m[ 5] = Value1.m[ 5];
		this->m[ 6] = Value1.m[ 6];	this->m[ 7] = Value1.m[7];	this->m[ 8] = Value1.m[ 8];
	}

	Matrix_3x3(const Matrix_4x4<double> &Value1) {
		this->m[ 0] = Value1.m[ 0];	this->m[ 1] = Value1.m[1];	this->m[ 2] = Value1.m[ 2];
		this->m[ 3] = Value1.m[ 4];	this->m[ 4] = Value1.m[5];	this->m[ 5] = Value1.m[ 6];
		this->m[ 6] = Value1.m[ 8];	this->m[ 7] = Value1.m[9];	this->m[ 8] = Value1.m[10];
	}

	Matrix_3x3(const Matrix_4x4<float> &Value1) {
		this->m[ 0] = Value1.m[ 0];	this->m[ 1] = Value1.m[1];	this->m[ 2] = Value1.m[ 2];
		this->m[ 3] = Value1.m[ 4];	this->m[ 4] = Value1.m[5];	this->m[ 5] = Value1.m[ 6];
		this->m[ 6] = Value1.m[ 8];	this->m[ 7] = Value1.m[9];	this->m[ 8] = Value1.m[10];
	}

	Matrix_3x3(const Matrix_4x4<int> &Value1) {
		this->m[ 0] = Value1.m[ 0];	this->m[ 1] = Value1.m[1];	this->m[ 2] = Value1.m[ 2];
		this->m[ 3] = Value1.m[ 4];	this->m[ 4] = Value1.m[5];	this->m[ 5] = Value1.m[ 6];
		this->m[ 6] = Value1.m[ 8];	this->m[ 7] = Value1.m[9];	this->m[ 8] = Value1.m[10];
	}

	void operator+= (const Matrix_3x3 &Value2) {
		this->m[0] += Value2.m[0]; this->m[1] += Value2.m[1]; this->m[2] += Value2.m[2];
		this->m[3] += Value2.m[3]; this->m[4] += Value2.m[4]; this->m[5] += Value2.m[5];
		this->m[6] += Value2.m[6]; this->m[7] += Value2.m[7]; this->m[8] += Value2.m[8];
	}

	void operator-= (const Matrix_3x3 &Value2) {
		this->m[0] -= Value2.m[0]; this->m[1] -= Value2.m[1]; this->m[2] -= Value2.m[2];
		this->m[3] -= Value2.m[3]; this->m[4] -= Value2.m[4]; this->m[5] -= Value2.m[5];
		this->m[6] -= Value2.m[6]; this->m[7] -= Value2.m[7]; this->m[8] -= Value2.m[8];
	}

	void operator*= (const Matrix_3x3 &Value2) {
		Matrix_3x3 _value3 = this;
		this->m[0] = _value3.m[0] * Value2.m[0] + _value3.m[1] * Value2.m[3] + _value3.m[2] * Value2.m[6];
		this->m[1] = _value3.m[0] * Value2.m[1] + _value3.m[1] * Value2.m[4] + _value3.m[2] * Value2.m[7];
		this->m[2] = _value3.m[0] * Value2.m[2] + _value3.m[1] * Value2.m[5] + _value3.m[2] * Value2.m[8];
		this->m[3] = _value3.m[3] * Value2.m[0] + _value3.m[4] * Value2.m[3] + _value3.m[5] * Value2.m[6];
		this->m[4] = _value3.m[3] * Value2.m[1] + _value3.m[4] * Value2.m[4] + _value3.m[5] * Value2.m[7];
		this->m[5] = _value3.m[3] * Value2.m[2] + _value3.m[4] * Value2.m[5] + _value3.m[5] * Value2.m[8];
		this->m[6] = _value3.m[6] * Value2.m[0] + _value3.m[7] * Value2.m[3] + _value3.m[8] * Value2.m[6];
		this->m[7] = _value3.m[6] * Value2.m[1] + _value3.m[7] * Value2.m[4] + _value3.m[8] * Value2.m[7];
		this->m[8] = _value3.m[6] * Value2.m[2] + _value3.m[7] * Value2.m[5] + _value3.m[8] * Value2.m[8];
	}

	

	void operator+= (const T &Value2) {
		this->m[0] += Value2; this->m[1] += Value2; this->m[2] += Value2;
		this->m[3] += Value2; this->m[4] += Value2; this->m[5] += Value2;
		this->m[6] += Value2; this->m[7] += Value2; this->m[8] += Value2;
	}

	void operator-= (const T &Value2) {
		this->m[0] -= Value2; this->m[1] -= Value2; this->m[2] -= Value2;
		this->m[3] -= Value2; this->m[4] -= Value2; this->m[5] -= Value2;
		this->m[6] -= Value2; this->m[7] -= Value2; this->m[8] -= Value2;
	}

	void operator*= (const T &Value2) {
		this->m[0] *= Value2; this->m[1] *= Value2; this->m[2] *= Value2;
		this->m[3] *= Value2; this->m[4] *= Value2; this->m[5] *= Value2;
		this->m[6] *= Value2; this->m[7] *= Value2; this->m[8] *= Value2;
	}

	void operator/= (const T &Value2) {
		this->m[0] /= Value2; this->m[1] /= Value2; this->m[2] /= Value2;
		this->m[3] /= Value2; this->m[4] /= Value2; this->m[5] /= Value2;
		this->m[6] /= Value2; this->m[7] /= Value2; this->m[8] /= Value2;
	}

	const T determinant(void) {
		return	this->m[0] * (this->m[4] * this->m[8] - this->m[5] * this->m[7])
				- this->m[1] * (this->m[3] * this->m[8] - this->m[5] * this->m[6])
				+ this->m[2] * (this->m[3] * this->m[7] - this->m[4] * this->m[6]);
	}

	void inverse(void) {
		
		const T _unit = 1;

		const T det = _unit / this->determinant();

		Matrix_3x3<T> _mat = *this;

		//	0	1	2
		//	3	4	5
		//	6	7	8
		
		this->m[0] = (_mat.m[4] * _mat.m[8] - _mat.m[5] * _mat.m[7]) * det;
		this->m[1] = (_mat.m[2] * _mat.m[7] - _mat.m[1] * _mat.m[8]) * det;
		this->m[2] = (_mat.m[1] * _mat.m[5] - _mat.m[2] * _mat.m[4]) * det;
		this->m[3] = (_mat.m[5] * _mat.m[6] - _mat.m[3] * _mat.m[8]) * det;
		this->m[4] = (_mat.m[0] * _mat.m[8] - _mat.m[2] * _mat.m[6]) * det;
		this->m[5] = (_mat.m[2] * _mat.m[3] - _mat.m[0] * _mat.m[5]) * det;
		this->m[6] = (_mat.m[3] * _mat.m[7] - _mat.m[4] * _mat.m[6]) * det;
		this->m[7] = (_mat.m[1] * _mat.m[6] - _mat.m[0] * _mat.m[7]) * det;
		this->m[8] = (_mat.m[0] * _mat.m[4] - _mat.m[1] * _mat.m[3]) * det;
	}

	void transpose(void) {
		Matrix_3x3<T> _mat = *this;
		//this->m[0] = _mat.m[0];
		this->m[1] = _mat.m[3];
		this->m[2] = _mat.m[6];							
		this->m[3] = _mat.m[1]; 
		//this->m[4] = _mat.m[4]; 
		this->m[5] = _mat.m[7];							
		this->m[6] = _mat.m[2]; 
		this->m[7] = _mat.m[5]; 
		//this->m[8] = _mat.m[8]);
	}



	// взаимодествие

	void operator= (const Matrix_3x3 Value1) {
		this->m[0] = Value1.m[0];
		this->m[1] = Value1.m[1];
		this->m[2] = Value1.m[2];
		this->m[3] = Value1.m[3];
		this->m[4] = Value1.m[4];
		this->m[5] = Value1.m[5];
		this->m[6] = Value1.m[6];
		this->m[7] = Value1.m[7];
		this->m[8] = Value1.m[8];
	}

	void operator= (const Matrix_4x4<T> Value1) {
		this->m[0] = Value1.m[0];
		this->m[1] = Value1.m[1];
		this->m[2] = Value1.m[2];
		this->m[3] = Value1.m[4];
		this->m[4] = Value1.m[5];
		this->m[5] = Value1.m[6];
		this->m[6] = Value1.m[8];
		this->m[7] = Value1.m[9];
		this->m[8] = Value1.m[10];
	}
};

template<class T>
Matrix_3x3<T> operator+ (const Matrix_3x3<T> &Value1, const Matrix_3x3<T> &Value2) {
		return Matrix_3x3<T>(	Value1.m[0] + Value2.m[0], Value1.m[1] + Value2.m[1], Value1.m[2] + Value2.m[2],
								Value1.m[3] + Value2.m[3], Value1.m[4] + Value2.m[4], Value1.m[5] + Value2.m[5],
								Value1.m[6] + Value2.m[6], Value1.m[7] + Value2.m[7], Value1.m[8] + Value2.m[8]);
}

template<class T>
Matrix_3x3<T> operator- (const Matrix_3x3<T> &Value1, const Matrix_3x3<T> &Value2) {
		return Matrix_3x3<T>(	Value1.m[0] - Value2.m[0], Value1.m[1] - Value2.m[1], Value1.m[2] - Value2.m[2],
							Value1.m[3] - Value2.m[3], Value1.m[4] - Value2.m[4], Value1.m[5] - Value2.m[5],
							Value1.m[6] - Value2.m[6], Value1.m[7] - Value2.m[7], Value1.m[8] - Value2.m[8]);
}

template<class T>
Matrix_3x3<T> operator* (const Matrix_3x3<T> &Value1, const Matrix_3x3<T> &Value2) {
		return Matrix_3x3<T>(	Value1.m[0] * Value2.m[0] + Value1.m[1] * Value2.m[3] + Value1.m[2] * Value2.m[6],
							Value1.m[0] * Value2.m[1] + Value1.m[1] * Value2.m[4] + Value1.m[2] * Value2.m[7],
							Value1.m[0] * Value2.m[2] + Value1.m[1] * Value2.m[5] + Value1.m[2] * Value2.m[8],
							Value1.m[3] * Value2.m[0] + Value1.m[4] * Value2.m[3] + Value1.m[5] * Value2.m[6],
							Value1.m[3] * Value2.m[1] + Value1.m[4] * Value2.m[4] + Value1.m[5] * Value2.m[7],
							Value1.m[3] * Value2.m[2] + Value1.m[4] * Value2.m[5] + Value1.m[5] * Value2.m[8],
							Value1.m[6] * Value2.m[0] + Value1.m[7] * Value2.m[3] + Value1.m[8] * Value2.m[6],
							Value1.m[6] * Value2.m[1] + Value1.m[7] * Value2.m[4] + Value1.m[8] * Value2.m[7],
							Value1.m[6] * Value2.m[2] + Value1.m[7] * Value2.m[5] + Value1.m[8] * Value2.m[8]);
}

template<class T>
Matrix_3x3<T> operator+ (const Matrix_3x3<T> &Value1, const T &Value2) {
		return Matrix_3x3<T>(	Value1.m[0] + Value2, Value1.m[1] + Value2, Value1.m[2] + Value2,
								Value1.m[3] + Value2, Value1.m[4] + Value2, Value1.m[5] + Value2,
								Value1.m[6] + Value2, Value1.m[7] + Value2, Value1.m[8] + Value2);
}

template<class T>
Matrix_3x3<T> operator- (const Matrix_3x3<T> &Value1, const T &Value2) {
		return Matrix_3x3<T>(	Value1.m[0] - Value2, Value1.m[1] - Value2, Value1.m[2] - Value2,
								Value1.m[3] - Value2, Value1.m[4] - Value2, Value1.m[5] - Value2,
								Value1.m[6] - Value2, Value1.m[7] - Value2, Value1.m[8] - Value2);
}

template<class T>
Matrix_3x3<T> operator* (const Matrix_3x3<T> &Value1, const T &Value2) {
		return Matrix_3x3<T>(	Value1.m[0] * Value2, Value1.m[1] * Value2, Value1.m[2] * Value2,
								Value1.m[3] * Value2, Value1.m[4] * Value2, Value1.m[5] * Value2,
								Value1.m[6] * Value2, Value1.m[7] * Value2, Value1.m[8] * Value2);
}

template<class T>
Matrix_3x3<T> operator/ (const Matrix_3x3<T> &Value1, const T &Value2) {
		return Matrix_3x3<T>(	Value1.m[0] / Value2, Value1.m[1] / Value2, Value1.m[2] / Value2,
								Value1.m[3] / Value2, Value1.m[4] / Value2, Value1.m[5] / Value2,
								Value1.m[6] / Value2, Value1.m[7] / Value2, Value1.m[8] / Value2);
}

template<class T>
const Vector_2<T> operator*(const Matrix_3x3<T> &Value1, const Vector_2<T> &Value2) {

	return Vector_2<T>(	Value1.m[0] * Value2.x + Value1.m[1] * Value2.y + Value1.m[2],
						Value1.m[3] * Value2.x + Value1.m[4] * Value2.y + Value1.m[5]);
}

template<class T>
const Vector_3<T> operator*(const Matrix_3x3<T> &Value1, const Vector_3<T> &Value2) {

	return Vector_3<T>(	Value1.m[0] * Value2.x + Value1.m[1] * Value2.y + Value1.m[2] * Value2.z,
						Value1.m[3] * Value2.x + Value1.m[4] * Value2.y + Value1.m[5] * Value2.z,
						Value1.m[6] * Value2.x + Value1.m[7] * Value2.y + Value1.m[8] * Value2.z);
}

template<class T>
T determinant(const Matrix_3x3<T> &Value1) {
		return	Value1.m[0] * (Value1.m[4] * Value1.m[8] - Value1.m[5] * Value1.m[7])
				- Value1.m[1] * (Value1.m[3] * Value1.m[8] - Value1.m[5] * Value1.m[6])
				+ Value1.m[2] * (Value1.m[3] * Value1.m[7] - Value1.m[4] * Value1.m[6]);
}

template<class T>
Matrix_3x3<T> inverse(const Matrix_3x3<T> &Value1) {
		
	const T _unit = 1;

	const T det = _unit / determinant(Value1);

	return Matrix_3x3<T>(	(Value1.m[4] * Value1.m[8] - Value1.m[5] * Value1.m[7]) * det,
							(Value1.m[2] * Value1.m[7] - Value1.m[1] * Value1.m[8]) * det,
							(Value1.m[1] * Value1.m[5] - Value1.m[2] * Value1.m[4]) * det,
							(Value1.m[5] * Value1.m[6] - Value1.m[3] * Value1.m[8]) * det,
							(Value1.m[0] * Value1.m[8] - Value1.m[2] * Value1.m[6]) * det,
							(Value1.m[2] * Value1.m[3] - Value1.m[0] * Value1.m[5]) * det,
							(Value1.m[3] * Value1.m[7] - Value1.m[4] * Value1.m[6]) * det,
							(Value1.m[1] * Value1.m[6] - Value1.m[0] * Value1.m[7]) * det,
							(Value1.m[0] * Value1.m[4] - Value1.m[1] * Value1.m[3]) * det);
}

template<class T>
Matrix_3x3<T> transpose(const Matrix_3x3<T> &Value1) {
		return Matrix_3x3<T>(	Value1.m[0], Value1.m[3], Value1.m[6],
								Value1.m[1], Value1.m[4], Value1.m[7],
								Value1.m[2], Value1.m[5], Value1.m[8]);
}
//-------------------------------------------------------
#endif // MATRIX_3X3_H