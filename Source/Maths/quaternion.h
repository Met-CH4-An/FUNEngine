#ifndef QUATERNION_H
#define QUATERNION_H
////////////////////////////////////////////////////////////////
/// хидеры
////////////////////////////////////////////////////////////////
#include "matrix_3x3.h"

template <class T>
struct TQuaternion;

typedef TQuaternion<float> Quaternion;

template <class T>
struct TQuaternion {

	T x = 0;
	T y = 0;
	T z = 0;
	T w = 0;

	Matrix_3x3<float> getMatrixRotation(void) {

		Matrix_3x3<float> _outMatrix;

		T xx = x * x;
		T xy = x * y;
		T xz = x * z;
		T xw = x * w;

		T yy = y * y;
		T yz = y * z;
		T yw = y * w;

		T zz = z * z;
		T zw = z * w;

		
		_outMatrix.m[0] = 1 - 2 * (yy + zz);
		_outMatrix.m[1] = 2 * (xy - zw);
		_outMatrix.m[2] = 2 * (xz + yw);

		_outMatrix.m[3] = 2 * (xy + zw);
		_outMatrix.m[4] = 1 - 2 * (xx + zz);
		_outMatrix.m[5] = 2 * (yz - xw);

		_outMatrix.m[6] = 2 * (xz - yw);
		_outMatrix.m[7] = 2 * (yz + xw);
		_outMatrix.m[8] = 1 - 2 * (xx + yy);
		//Далее заполняем четвёртый ряд и четвёртый столбец матрицы 4х4:
		//_outMatrix.m[3] = _outMatrix.m[7] = _outMatrix.m[11] = _outMatrix.m[12] = _outMatrix.m[13] = _outMatrix.m[14] = 0;
		//_outMatrix.m[15] = 1;

		

		return _outMatrix;

	}

}; // struct TQuaternion



#endif // QUATERNION_H