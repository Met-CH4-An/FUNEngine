#ifndef MATRIX_4x4_H
#define MATRIX_4x4_H

#include "math.h"

template <class T>
class Matrix_4x4;

#include "matrix_3x3.h"
#include "vector_2.h"
#include "vector_3.h"
#include "vector_4.h"

typedef Matrix_4x4<int>		mat4i;
typedef Matrix_4x4<float>	mat4;
typedef Matrix_4x4<double>	mat4d;
//*************************************************************************************************
//Класс:	Matrix_4x4
//Описание:	Обработка матриц 4 на 4
//*************************************************************************************************
template <typename T>
class Matrix_4x4 {

public:

	T m[16];

	Matrix_4x4() {
		this->m[0] = 1;		this->m[1] = 0;		this->m[2] = 0;		this->m[3] = 0;
		this->m[4] = 0;		this->m[5] = 1;		this->m[6] = 0;		this->m[7] = 0;
		this->m[8] = 0;		this->m[9] = 0;		this->m[10] = 1;	this->m[11] = 0;
		this->m[12] = 0;	this->m[13] = 0;	this->m[14] = 0;	this->m[15] = 1;
	}

	Matrix_4x4(	T Value1,	T Value2,	T Value3,	T Value4,
				T Value5,	T Value6,	T Value7,	T Value8,
				T Value9,	T Value10,	T Value11,	T Value12,
				T Value13,	T Value14,	T Value15,	T Value16) {
		this->m[ 0] = Value1;		this->m[ 1] = Value2;		this->m[ 2] = Value3;		this->m[ 3] = Value4;
		this->m[ 4] = Value5;		this->m[ 5] = Value6;		this->m[ 6] = Value7;		this->m[ 7] = Value8;
		this->m[ 8] = Value9;		this->m[ 9] = Value10;		this->m[10] = Value11;		this->m[11] = Value12;
		this->m[12] = Value13;		this->m[13] = Value14;		this->m[14] = Value15;		this->m[15] = Value16;
	}

	Matrix_4x4(Matrix_3x3<T> Value1) {
		this->m[ 0] = Value1.m[0];
		this->m[ 1] = Value1.m[1];
		this->m[ 2] = Value1.m[2];
		this->m[ 3] = 0;

		this->m[ 4] = Value1.m[3];
		this->m[ 5] = Value1.m[4];
		this->m[ 6] = Value1.m[5];
		this->m[ 7] = 0;

		this->m[ 8] = Value1.m[6];
		this->m[ 9] = Value1.m[7];
		this->m[10] = Value1.m[8];
		this->m[11] = 0;

		this->m[12] = 0;
		this->m[13] = 0;
		this->m[14] = 0;
		this->m[15] = 1;
	}

	void operator+= (const Matrix_4x4 &Value1) {
		this->m[ 0] += Value1.m[0];	this->m[ 1] += Value1.m[1];	this->m[ 2] += Value1.m[2];	this->m[ 3] += Value1.m[3];
		this->m[ 4] += Value1.m[4];	this->m[ 5] += Value1.m[5];	this->m[ 6] += Value1.m[6];	this->m[ 7] += Value1.m[7];
		this->m[ 8] += Value1.m[8];	this->m[ 9] += Value1.m[9];	this->m[10] += Value1.m[10];	this->m[11] += Value1.m[11];
		this->m[12] += Value1.m[12];	this->m[13] += Value1.m[13];	this->m[14] += Value1.m[14];	this->m[15] += Value1.m[15];
	}

	void operator-= (const Matrix_4x4 &Value1) {
		this->m[ 0] -= Value1.m[ 0];	this->m[ 1] -= Value1.m[ 1];	this->m[ 2] -= Value1.m[ 2];	this->m[ 3] -= Value1.m[ 3];
		this->m[ 4] -= Value1.m[ 4];	this->m[ 5] -= Value1.m[ 5];	this->m[ 6] -= Value1.m[ 6];	this->m[ 7] -= Value1.m[ 7];
		this->m[ 8] -= Value1.m[ 8];	this->m[ 9] -= Value1.m[ 9];	this->m[10] -= Value1.m[10];	this->m[11] -= Value1.m[11];
		this->m[12] -= Value1.m[12];	this->m[13] -= Value1.m[13];	this->m[14] -= Value1.m[14];	this->m[15] -= Value1.m[15];
	}

	void operator*= (const Matrix_4x4 &Value1) {
		Matrix_4x4 _mat = *this;
		this->m[ 0] = _mat.m[ 0] * Value1.m[ 0] + _mat.m[ 1] * Value1.m[ 4] + _mat.m[ 2] * Value1.m[ 8] + _mat.m[ 3] * Value1.m[12];
		this->m[ 1] = _mat.m[ 0] * Value1.m[ 1] + _mat.m[ 1] * Value1.m[ 5] + _mat.m[ 2] * Value1.m[ 9] + _mat.m[ 3] * Value1.m[13];
		this->m[ 2] = _mat.m[ 0] * Value1.m[ 2] + _mat.m[ 1] * Value1.m[ 6] + _mat.m[ 2] * Value1.m[10] + _mat.m[ 3] * Value1.m[14];
		this->m[ 3] = _mat.m[ 0] * Value1.m[ 3] + _mat.m[ 1] * Value1.m[ 7] + _mat.m[ 2] * Value1.m[11] + _mat.m[ 3] * Value1.m[15];
		this->m[ 4] = _mat.m[ 4] * Value1.m[ 0] + _mat.m[ 5] * Value1.m[ 4] + _mat.m[ 6] * Value1.m[ 8] + _mat.m[ 7] * Value1.m[12];
		this->m[ 5] = _mat.m[ 4] * Value1.m[ 1] + _mat.m[ 5] * Value1.m[ 5] + _mat.m[ 6] * Value1.m[ 9] + _mat.m[ 7] * Value1.m[13];
		this->m[ 6] = _mat.m[ 4] * Value1.m[ 2] + _mat.m[ 5] * Value1.m[ 6] + _mat.m[ 6] * Value1.m[10] + _mat.m[ 7] * Value1.m[14];
		this->m[ 7] = _mat.m[ 4] * Value1.m[ 3] + _mat.m[ 5] * Value1.m[ 7] + _mat.m[ 6] * Value1.m[11] + _mat.m[ 7] * Value1.m[15];
		this->m[ 8] = _mat.m[ 8] * Value1.m[ 0] + _mat.m[ 9] * Value1.m[ 4] + _mat.m[10] * Value1.m[ 8] + _mat.m[11] * Value1.m[12];
		this->m[ 9] = _mat.m[ 8] * Value1.m[ 1] + _mat.m[ 9] * Value1.m[ 5] + _mat.m[10] * Value1.m[ 9] + _mat.m[11] * Value1.m[13];
		this->m[10] = _mat.m[ 8] * Value1.m[ 2] + _mat.m[ 9] * Value1.m[ 6] + _mat.m[10] * Value1.m[10] + _mat.m[11] * Value1.m[14];
		this->m[11] = _mat.m[ 8] * Value1.m[ 3] + _mat.m[ 9] * Value1.m[ 7] + _mat.m[10] * Value1.m[11] + _mat.m[11] * Value1.m[15];
		this->m[12] = _mat.m[12] * Value1.m[ 0] + _mat.m[13] * Value1.m[ 4] + _mat.m[14] * Value1.m[ 8] + _mat.m[15] * Value1.m[12];
		this->m[13] = _mat.m[12] * Value1.m[ 1] + _mat.m[13] * Value1.m[ 5] + _mat.m[14] * Value1.m[ 9] + _mat.m[15] * Value1.m[13];
		this->m[14] = _mat.m[12] * Value1.m[ 2] + _mat.m[13] * Value1.m[ 6] + _mat.m[14] * Value1.m[10] + _mat.m[15] * Value1.m[14];
		this->m[15] = _mat.m[12] * Value1.m[ 3] + _mat.m[13] * Value1.m[ 7] + _mat.m[14] * Value1.m[11] + _mat.m[15] * Value1.m[15];
	}

	

	void operator+= (const T &Value1) {
		this->m[ 0] += Value1;	this->m[ 1] += Value1;	this->m[ 2] += Value1;	this->m[ 3] += Value1;
		this->m[ 4] += Value1;	this->m[ 5] += Value1;	this->m[ 6] += Value1;	this->m[ 7] += Value1;
		this->m[ 8] += Value1;	this->m[ 9] += Value1;	this->m[10] += Value1;	this->m[11] += Value1;
		this->m[12] += Value1;	this->m[13] += Value1;	this->m[14] += Value1;	this->m[15] += Value1;
	}

	void operator-= (const T &Value1) {
		this->m[ 0] -= Value1;	this->m[ 1] -= Value1;	this->m[ 2] -= Value1;	this->m[ 3] -= Value1;
		this->m[ 4] -= Value1;	this->m[ 5] -= Value1;	this->m[ 6] -= Value1;	this->m[ 7] -= Value1;
		this->m[ 8] -= Value1;	this->m[ 9] -= Value1;	this->m[10] -= Value1;	this->m[11] -= Value1;
		this->m[12] -= Value1;	this->m[13] -= Value1;	this->m[14] -= Value1;	this->m[15] -= Value1;
	}

	void operator*= (const T &Value1) {
		this->m[ 0] *= Value1;	this->m[ 1] *= Value1;	this->m[ 2] *= Value1;	this->m[ 3] *= Value1;
		this->m[ 4] *= Value1;	this->m[ 5] *= Value1;	this->m[ 6] *= Value1;	this->m[ 7] *= Value1;
		this->m[ 8] *= Value1;	this->m[ 9] *= Value1;	this->m[10] *= Value1;	this->m[11] *= Value1;
		this->m[12] *= Value1;	this->m[13] *= Value1;	this->m[14] *= Value1;	this->m[15] *= Value1;
	}

	void operator/= (const T &Value1) {
		this->m[ 0] /= Value1;	this->m[ 1] /= Value1;	this->m[ 2] /= Value1;	this->m[ 3] /= Value1;
		this->m[ 4] /= Value1;	this->m[ 5] /= Value1;	this->m[ 6] /= Value1;	this->m[ 7] /= Value1;
		this->m[ 8] /= Value1;	this->m[ 9] /= Value1;	this->m[10] /= Value1;	this->m[11] /= Value1;
		this->m[12] /= Value1;	this->m[13] /= Value1;	this->m[14] /= Value1;	this->m[15] /= Value1;
	}

	

	T determinant(void) {
		T A, B, C, D, E, F;
		A = this->m[10] * this->m[15] - this->m[11] * this->m[14];
		B = this->m[ 9] * this->m[15] - this->m[11] * this->m[13];
		C = this->m[ 9] * this->m[14] - this->m[10] * this->m[13];
		D = this->m[ 8] * this->m[15] - this->m[11] * this->m[12];
		E = this->m[ 8] * this->m[14] - this->m[10] * this->m[12];
		F = this->m[ 8] * this->m[13] - this->m[ 9] * this->m[12];

		return	  this->m[0] * (A * this->m[5] - B * this->m[6] + C * this->m[7])
				- this->m[1] * (A * this->m[4] - D * this->m[6] + E * this->m[7])
				+ this->m[2] * (B * this->m[4] - D * this->m[5] + F * this->m[7])
				- this->m[3] * (C * this->m[4] - E * this->m[5] + F * this->m[6]);
	}

	void inverse(void) {
		const T _unit = 1;
		
		const T det = _unit / this->determinant();

		#define MDET3(a0,a1,a2,a3,a4,a5,a6,a7,a8) \
					( a0 * (a4 * a8 - a5 * a7) \
					- a1 * (a3 * a8 - a5 * a6) \
					+ a2 * (a3 * a7 - a4 * a6) )

		// ~ 160 mul & 80 add
		this->m[ 0] = (MDET3(this->m[5], this->m[6], this->m[7], this->m[9], this->m[10], this->m[11], this->m[13], this->m[14], this->m[15])) * det;
		this->m[ 1] = (-MDET3(this->m[1], this->m[2], this->m[3], this->m[9], this->m[10], this->m[11], this->m[13], this->m[14], this->m[15])) * det;
		this->m[ 2] = (MDET3(this->m[1], this->m[2], this->m[3], this->m[5], this->m[ 6], this->m[ 7], this->m[13], this->m[14], this->m[15])) * det;
		this->m[ 3] = (-MDET3(this->m[1], this->m[2], this->m[3], this->m[5], this->m[ 6], this->m[ 7], this->m[ 9], this->m[10], this->m[11])) * det;
		this->m[ 4] = (-MDET3(this->m[4], this->m[6], this->m[7], this->m[8], this->m[10], this->m[11], this->m[12], this->m[14], this->m[15])) * det;
		this->m[ 5] = (MDET3(this->m[0], this->m[2], this->m[3], this->m[8], this->m[10], this->m[11], this->m[12], this->m[14], this->m[15])) * det;
		this->m[ 6] = (-MDET3(this->m[0], this->m[2], this->m[3], this->m[4], this->m[ 6], this->m[ 7], this->m[12], this->m[14], this->m[15])) * det;
		this->m[ 7] = (MDET3(this->m[0], this->m[2], this->m[3], this->m[4], this->m[ 6], this->m[ 7], this->m[ 8], this->m[10], this->m[11])) * det;
		this->m[ 8] = (MDET3(this->m[4], this->m[5], this->m[7], this->m[8], this->m[ 9], this->m[11], this->m[12], this->m[13], this->m[15])) * det;
		this->m[ 9] = (-MDET3(this->m[0], this->m[1], this->m[3], this->m[8], this->m[ 9], this->m[11], this->m[12], this->m[13], this->m[15])) * det;
		this->m[10] = (MDET3(this->m[0], this->m[1], this->m[3], this->m[4], this->m[ 5], this->m[ 7], this->m[12], this->m[13], this->m[15])) * det;
		this->m[11] = (-MDET3(this->m[0], this->m[1], this->m[3], this->m[4], this->m[ 5], this->m[ 7], this->m[ 8], this->m[ 9], this->m[11])) * det;
		this->m[12] = (-MDET3(this->m[4], this->m[5], this->m[6], this->m[8], this->m[ 9], this->m[10], this->m[12], this->m[13], this->m[14])) * det;
		this->m[13] = (MDET3(this->m[0], this->m[1], this->m[2], this->m[8], this->m[ 9], this->m[10], this->m[12], this->m[13], this->m[14])) * det;
		this->m[14] = (-MDET3(this->m[0], this->m[1], this->m[2], this->m[4], this->m[ 5], this->m[ 6], this->m[12], this->m[13], this->m[14])) * det;
		this->m[15] = (MDET3(this->m[0], this->m[1], this->m[2], this->m[4], this->m[ 5], this->m[ 6], this->m[ 8], this->m[ 9], this->m[10])) * det;

		#undef MDET3
	}

	void transpose(void) {
	
		Matrix_4x4<T> _mat = *this;
		//this->m[ 0] = _mat.m[ 0],
		this->m[ 1] = _mat.m[ 4];
		this->m[ 2] = _mat.m[ 8]; 
		this->m[ 3] = _mat.m[12];
		this->m[ 4] = _mat.m[ 1];
		//this->m[ 5] = _mat.m[ 5], 
		this->m[ 6] = _mat.m[ 9]; 
		this->m[ 7] = _mat.m[13];
		this->m[ 8] = _mat.m[ 2];
		this->m[ 9] = _mat.m[ 6];
		//this->m[10] = _mat.m[10],
		this->m[11] = _mat.m[14];
		this->m[12] = _mat.m[ 3];
		this->m[13] = _mat.m[ 7];
		this->m[14] = _mat.m[11];
		//this->m[15] = _mat.m[15]);
	}

	// взаимодествие

	void operator= (const Matrix_4x4<T> Value1) {
		this->m[ 0] = Value1.m[ 0];
		this->m[ 1] = Value1.m[ 1];
		this->m[ 2] = Value1.m[ 2];
		this->m[ 3] = Value1.m[ 3];

		this->m[ 4] = Value1.m[ 4];
		this->m[ 5] = Value1.m[ 5];
		this->m[ 6] = Value1.m[ 6];
		this->m[ 7] = Value1.m[ 7];

		this->m[ 8] = Value1.m[ 8];
		this->m[ 9] = Value1.m[ 9];
		this->m[10] = Value1.m[10];
		this->m[11] = Value1.m[11];

		this->m[12] = Value1.m[12];
		this->m[13] = Value1.m[13];
		this->m[14] = Value1.m[14];
		this->m[15] = Value1.m[15];
	}

	void operator= (const Matrix_3x3<T> Value1) {
		this->m[ 0] = Value1.m[0];
		this->m[ 1] = Value1.m[1];
		this->m[ 2] = Value1.m[2];
		this->m[ 3] = 0;

		this->m[ 4] = Value1.m[3];
		this->m[ 5] = Value1.m[4];
		this->m[ 6] = Value1.m[5];
		this->m[ 7] = 0;

		this->m[ 8] = Value1.m[6];
		this->m[ 9] = Value1.m[7];
		this->m[10] = Value1.m[8];
		this->m[11] = 0;

		this->m[12] = 0;
		this->m[13] = 0;
		this->m[14] = 0;
		this->m[15] = 1;
	}

	Matrix_3x3<T> mat3(void) {
		return Matrix_3x3<T>(	this->m[ 0], this->m[ 1], this->m[ 2],
								this->m[ 4], this->m[ 5], this->m[ 6],
								this->m[ 8], this->m[ 9], this->m[10]);
	}

};

template<class T>
Matrix_4x4<T> operator+ (const Matrix_4x4<T> &Value1, const Matrix_4x4<T> &Value2) {
		return Matrix_4x4<T>(	Value1.m[ 0] + Value2.m[0],		Value1.m[ 1] + Value2.m[1],		Value1.m[ 2] + Value2.m[2],		Value1.m[ 3] + Value2.m[3],
								Value1.m[ 4] + Value2.m[4],		Value1.m[ 5] + Value2.m[5],		Value1.m[ 6] + Value2.m[6],		Value1.m[ 7] + Value2.m[7],
								Value1.m[ 8] + Value2.m[8],		Value1.m[ 9] + Value2.m[9],		Value1.m[10] + Value2.m[10],	Value1.m[11] + Value2.m[11],
								Value1.m[12] + Value2.m[12],	Value1.m[13] + Value2.m[13],	Value1.m[14] + Value2.m[14],	Value1.m[15] + Value2.m[15]);
}

template<class T>
Matrix_4x4<T> operator- (const Matrix_4x4<T> &Value1, const Matrix_4x4<T> &Value2) {
		return Matrix_4x4<T>(	Value1.m[ 0] - Value2.m[0],		Value1.m[ 1] - Value2.m[1],		Value1.m[ 2] - Value2.m[2],		Value1.m[ 3] - Value2.m[3],
								Value1.m[ 4] - Value2.m[4],		Value1.m[ 5] - Value2.m[5],		Value1.m[ 6] - Value2.m[6],		Value1.m[ 7] - Value2.m[7],
								Value1.m[ 8] - Value2.m[8],		Value1.m[ 9] - Value2.m[9],		Value1.m[10] - Value2.m[10],	Value1.m[11] - Value2.m[11],
								Value1.m[12] - Value2.m[12],	Value1.m[13] - Value2.m[13],	Value1.m[14] - Value2.m[14],	Value1.m[15] - Value2.m[15]);
}

template<class T>
Matrix_4x4<T> operator* (const Matrix_4x4<T> &Value1, const Matrix_4x4<T> &Value2) {
		return Matrix_4x4<T>(	Value1.m[ 0] * Value2.m[ 0] + Value1.m[ 1] * Value2.m[ 4] + Value1.m[ 2] * Value2.m[ 8] + Value1.m[ 3] * Value2.m[12],
								Value1.m[ 0] * Value2.m[ 1] + Value1.m[ 1] * Value2.m[ 5] + Value1.m[ 2] * Value2.m[ 9] + Value1.m[ 3] * Value2.m[13],
								Value1.m[ 0] * Value2.m[ 2] + Value1.m[ 1] * Value2.m[ 6] + Value1.m[ 2] * Value2.m[10] + Value1.m[ 3] * Value2.m[14],
								Value1.m[ 0] * Value2.m[ 3] + Value1.m[ 1] * Value2.m[ 7] + Value1.m[ 2] * Value2.m[11] + Value1.m[ 3] * Value2.m[15],
								Value1.m[ 4] * Value2.m[ 0] + Value1.m[ 5] * Value2.m[ 4] + Value1.m[ 6] * Value2.m[ 8] + Value1.m[ 7] * Value2.m[12],
								Value1.m[ 4] * Value2.m[ 1] + Value1.m[ 5] * Value2.m[ 5] + Value1.m[ 6] * Value2.m[ 9] + Value1.m[ 7] * Value2.m[13],
								Value1.m[ 4] * Value2.m[ 2] + Value1.m[ 5] * Value2.m[ 6] + Value1.m[ 6] * Value2.m[10] + Value1.m[ 7] * Value2.m[14],
								Value1.m[ 4] * Value2.m[ 3] + Value1.m[ 5] * Value2.m[ 7] + Value1.m[ 6] * Value2.m[11] + Value1.m[ 7] * Value2.m[15],
								Value1.m[ 8] * Value2.m[ 0] + Value1.m[ 9] * Value2.m[ 4] + Value1.m[10] * Value2.m[ 8] + Value1.m[11] * Value2.m[12],
								Value1.m[ 8] * Value2.m[ 1] + Value1.m[ 9] * Value2.m[ 5] + Value1.m[10] * Value2.m[ 9] + Value1.m[11] * Value2.m[13],
								Value1.m[ 8] * Value2.m[ 2] + Value1.m[ 9] * Value2.m[ 6] + Value1.m[10] * Value2.m[10] + Value1.m[11] * Value2.m[14],
								Value1.m[ 8] * Value2.m[ 3] + Value1.m[ 9] * Value2.m[ 7] + Value1.m[10] * Value2.m[11] + Value1.m[11] * Value2.m[15],
								Value1.m[12] * Value2.m[ 0] + Value1.m[13] * Value2.m[ 4] + Value1.m[14] * Value2.m[ 8] + Value1.m[15] * Value2.m[12],
								Value1.m[12] * Value2.m[ 1] + Value1.m[13] * Value2.m[ 5] + Value1.m[14] * Value2.m[ 9] + Value1.m[15] * Value2.m[13],
								Value1.m[12] * Value2.m[ 2] + Value1.m[13] * Value2.m[ 6] + Value1.m[14] * Value2.m[10] + Value1.m[15] * Value2.m[14],
								Value1.m[12] * Value2.m[ 3] + Value1.m[13] * Value2.m[ 7] + Value1.m[14] * Value2.m[11] + Value1.m[15] * Value2.m[15]);
}

template<class T>
Matrix_4x4<T> operator+ (const Matrix_4x4<T> &Value1, const T &Value2) {
		return Matrix_4x4<T>(	Value1.m[ 0] + Value2,	Value1.m[ 1] + Value2,	Value1.m[ 2] + Value2,	Value1.m[ 3] + Value2,
								Value1.m[ 4] + Value2,	Value1.m[ 5] + Value2,	Value1.m[ 6] + Value2,	Value1.m[ 7] + Value2,
								Value1.m[ 8] + Value2,	Value1.m[ 9] + Value2,	Value1.m[10] + Value2,	Value1.m[11] + Value2,
								Value1.m[12] + Value2,	Value1.m[13] + Value2,	Value1.m[14] + Value2,	Value1.m[15] + Value2);
}

template<class T>
Matrix_4x4<T> operator- (const Matrix_4x4<T> &Value1, const T &Value2) {
		return Matrix_4x4<T>(	Value1.m[ 0] - Value2,	Value1.m[ 1] - Value2,	Value1.m[ 2] - Value2,	Value1.m[ 3] - Value2,
								Value1.m[ 4] - Value2,	Value1.m[ 5] - Value2,	Value1.m[ 6] - Value2,	Value1.m[ 7] - Value2,
								Value1.m[ 8] - Value2,	Value1.m[ 9] - Value2,	Value1.m[10] - Value2,	Value1.m[11] - Value2,
								Value1.m[12] - Value2,	Value1.m[13] - Value2,	Value1.m[14] - Value2,	Value1.m[15] - Value2);
}

template<class T>
Matrix_4x4<T> operator* (const Matrix_4x4<T> &Value1, const T &Value2) {
		return Matrix_4x4<T>(	Value1.m[ 0] * Value2,	Value1.m[ 1] * Value2,	Value1.m[ 2] * Value2,	Value1.m[ 3] * Value2,
								Value1.m[ 4] * Value2,	Value1.m[ 5] * Value2,	Value1.m[ 6] * Value2,	Value1.m[ 7] * Value2,
								Value1.m[ 8] * Value2,	Value1.m[ 9] * Value2,	Value1.m[10] * Value2,	Value1.m[11] * Value2,
								Value1.m[12] * Value2,	Value1.m[13] * Value2,	Value1.m[14] * Value2,	Value1.m[15] * Value2);
}

template<class T>
Matrix_4x4<T> operator/ (const Matrix_4x4<T> &Value1, const T &Value2) {
		return Matrix_4x4<T>(	Value1.m[ 0] / Value2,	Value1.m[ 1] / Value2,	Value1.m[ 2] / Value2,	Value1.m[ 3] / Value2,
								Value1.m[ 4] / Value2,	Value1.m[ 5] / Value2,	Value1.m[ 6] / Value2,	Value1.m[ 7] / Value2,
								Value1.m[ 8] / Value2,	Value1.m[ 9] / Value2,	Value1.m[10] / Value2,	Value1.m[11] / Value2,
								Value1.m[12] / Value2,	Value1.m[13] / Value2,	Value1.m[14] / Value2,	Value1.m[15] / Value2);
}

template<class T>
const Vector_2<T> operator*(const Matrix_4x4<T> &Value1, const Vector_2<T> &Value2) {

	return  Vector_2<T>(	Value1.m[0] * Value2.x + Value1.m[1] * Value2.y + Value1.m[2] + Value1.m[3],
							Value1.m[4] * Value2.x + Value1.m[5] * Value2.y + Value1.m[6] + Value1.m[7]);
}

template<class T>
const Vector_3<T> operator*(const Matrix_4x4<T> &Value1, const Vector_3<T> &Value2) {

	return Vector_3<T>(	Value1.m[ 0] * Value2.x + Value1.m[ 1] * Value2.y + Value1.m[ 2] * Value2.z + Value1.m[ 3],
							Value1.m[ 4] * Value2.x + Value1.m[ 5] * Value2.y + Value1.m[ 6] * Value2.z + Value1.m[ 7],
							Value1.m[ 8] * Value2.x + Value1.m[ 9] * Value2.y + Value1.m[10] * Value2.z + Value1.m[11]);
}

template<class T>
const Vector_4<T> operator*(const Matrix_4x4<T> &Value1, const Vector_4<T> &Value2) {

	return Vector_4<T>(	Value1.m[ 0] * Value2.x + Value1.m[ 1] * Value2.y + Value1.m[ 2] * Value2.z + Value1.m[ 3] * Value2.w,
							Value1.m[ 4] * Value2.x + Value1.m[ 5] * Value2.y + Value1.m[ 6] * Value2.z + Value1.m[ 7] * Value2.w,
							Value1.m[ 8] * Value2.x + Value1.m[ 9] * Value2.y + Value1.m[10] * Value2.z + Value1.m[11] * Value2.w,
							Value1.m[12] * Value2.x + Value1.m[13] * Value2.y + Value1.m[14] * Value2.z + Value1.m[15] * Value2.w);
}

template<class T>
T determinant(const Matrix_4x4<T> &Value1) {
		T A, B, C, D, E, F;
		A = Value1.m[10] * Value1.m[15] - Value1.m[11] * Value1.m[14];
		B = Value1.m[ 9] * Value1.m[15] - Value1.m[11] * Value1.m[13];
		C = Value1.m[ 9] * Value1.m[14] - Value1.m[10] * Value1.m[13];
		D = Value1.m[ 8] * Value1.m[15] - Value1.m[11] * Value1.m[12];
		E = Value1.m[ 8] * Value1.m[14] - Value1.m[10] * Value1.m[12];
		F = Value1.m[ 8] * Value1.m[13] - Value1.m[ 9] * Value1.m[12];

		return	  Value1.m[0] * (A * Value1.m[5] - B * Value1.m[6] + C * Value1.m[7])
				- Value1.m[1] * (A * Value1.m[4] - D * Value1.m[6] + E * Value1.m[7])
				+ Value1.m[2] * (B * Value1.m[4] - D * Value1.m[5] + F * Value1.m[7])
				- Value1.m[3] * (C * Value1.m[4] - E * Value1.m[5] + F * Value1.m[6]);
}

template<class T>
Matrix_4x4<T> inverse(const Matrix_4x4<T> &Value1) {
	const T _unit = 1;
		
	const T det = _unit / determinant(Value1);
	#define MDET3(a0,a1,a2,a3,a4,a5,a6,a7,a8) \
				( a0 * (a4 * a8 - a5 * a7) \
				- a1 * (a3 * a8 - a5 * a6) \
				+ a2 * (a3 * a7 - a4 * a6) )
	// ~ 160 mul & 80 add
	return Matrix_4x4<T>(	 MDET3(Value1.m[5], Value1.m[6], Value1.m[7], Value1.m[9], Value1.m[10], Value1.m[11], Value1.m[13], Value1.m[14], Value1.m[15]) * det,
							-MDET3(Value1.m[1], Value1.m[2], Value1.m[3], Value1.m[9], Value1.m[10], Value1.m[11], Value1.m[13], Value1.m[14], Value1.m[15]) * det,
							 MDET3(Value1.m[1], Value1.m[2], Value1.m[3], Value1.m[5], Value1.m[ 6], Value1.m[ 7], Value1.m[13], Value1.m[14], Value1.m[15]) * det,
							-MDET3(Value1.m[1], Value1.m[2], Value1.m[3], Value1.m[5], Value1.m[ 6], Value1.m[ 7], Value1.m[ 9], Value1.m[10], Value1.m[11]) * det,
							-MDET3(Value1.m[4], Value1.m[6], Value1.m[7], Value1.m[8], Value1.m[10], Value1.m[11], Value1.m[12], Value1.m[14], Value1.m[15]) * det,
							 MDET3(Value1.m[0], Value1.m[2], Value1.m[3], Value1.m[8], Value1.m[10], Value1.m[11], Value1.m[12], Value1.m[14], Value1.m[15]) * det,
							-MDET3(Value1.m[0], Value1.m[2], Value1.m[3], Value1.m[4], Value1.m[ 6], Value1.m[ 7], Value1.m[12], Value1.m[14], Value1.m[15]) * det,
							 MDET3(Value1.m[0], Value1.m[2], Value1.m[3], Value1.m[4], Value1.m[ 6], Value1.m[ 7], Value1.m[ 8], Value1.m[10], Value1.m[11]) * det,
							 MDET3(Value1.m[4], Value1.m[5], Value1.m[7], Value1.m[8], Value1.m[ 9], Value1.m[11], Value1.m[12], Value1.m[13], Value1.m[15]) * det,
							-MDET3(Value1.m[0], Value1.m[1], Value1.m[3], Value1.m[8], Value1.m[ 9], Value1.m[11], Value1.m[12], Value1.m[13], Value1.m[15]) * det,
							 MDET3(Value1.m[0], Value1.m[1], Value1.m[3], Value1.m[4], Value1.m[ 5], Value1.m[ 7], Value1.m[12], Value1.m[13], Value1.m[15]) * det,
							-MDET3(Value1.m[0], Value1.m[1], Value1.m[3], Value1.m[4], Value1.m[ 5], Value1.m[ 7], Value1.m[ 8], Value1.m[ 9], Value1.m[11]) * det,
							-MDET3(Value1.m[4], Value1.m[5], Value1.m[6], Value1.m[8], Value1.m[ 9], Value1.m[10], Value1.m[12], Value1.m[13], Value1.m[14]) * det,
							 MDET3(Value1.m[0], Value1.m[1], Value1.m[2], Value1.m[8], Value1.m[ 9], Value1.m[10], Value1.m[12], Value1.m[13], Value1.m[14]) * det,
							-MDET3(Value1.m[0], Value1.m[1], Value1.m[2], Value1.m[4], Value1.m[ 5], Value1.m[ 6], Value1.m[12], Value1.m[13], Value1.m[14]) * det,
							 MDET3(Value1.m[0], Value1.m[1], Value1.m[2], Value1.m[4], Value1.m[ 5], Value1.m[ 6], Value1.m[ 8], Value1.m[ 9], Value1.m[10]) * det);
	#undef MDET3
}

template<class T>
Matrix_4x4<T> transpose(const Matrix_4x4<T> &Value1) {

	return Matrix_4x4<T>(	Value1.m[ 0], Value1.m[ 4], Value1.m[ 8], Value1.m[12],
							Value1.m[ 1], Value1.m[ 5], Value1.m[ 9], Value1.m[13],
							Value1.m[ 2], Value1.m[ 6], Value1.m[10], Value1.m[14],
							Value1.m[ 3], Value1.m[ 7], Value1.m[11], Value1.m[15]);
}
#endif // MATRIX_4_4_H