#include "mat4x4.h"

mat4x4::mat4x4() {
	mat[0] = 1.0f;  mat[4] = 0.0f;  mat[8]  = 0.0f; mat[12] = 0.0f;
	mat[1] = 0.0f;  mat[5] = 1.0f;  mat[9]  = 0.0f; mat[13] = 0.0f;
	mat[2] = 0.0f;  mat[6] = 0.0f;  mat[10] = 1.0f; mat[14] = 0.0f;
	mat[3] = 0.0f;  mat[7] = 0.0f;  mat[11] = 0.0f; mat[15] = 1.0f;
}

mat4x4::mat4x4(GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03,
			   GLfloat m10, GLfloat m11, GLfloat m12, GLfloat m13,
			   GLfloat m20, GLfloat m21, GLfloat m22, GLfloat m23,
			   GLfloat m30, GLfloat m31, GLfloat m32, GLfloat m33) {


	mat[0] = m00;  mat[4] = m01;  mat[8] = m02; mat[12] = m03;
	mat[1] = m10;  mat[5] = m11;  mat[9] = m12; mat[13] = m13;
	mat[2] = m20;  mat[6] = m21;  mat[10] = m22; mat[14] = m23;
	mat[3] = m30;  mat[7] = m31;  mat[11] = m32; mat[15] = m33;
}

mat4x4::mat4x4(GLfloat value) {
	mat[0] = value;  mat[4] = value;  mat[8] = value; mat[12] = value;
	mat[1] = value;  mat[5] = value;  mat[9] = value; mat[13] = value;
	mat[2] = value;  mat[6] = value;  mat[10] = value; mat[14] = value;
	mat[3] = value;  mat[7] = value;  mat[11] = value; mat[15] = value;
}

mat4x4::~mat4x4() {

}

mat4x4 mat4x4::identity() {
	mat4x4 idn(0.0f);
	idn.mat[0] = 1.0;
	idn.mat[5] = 1.0;
	idn.mat[10] = 1.0;
	idn.mat[15] = 1.0;
	return idn;
}
mat4x4 mat4x4::operator *(const mat4x4& b)const {
	mat4x4 result(0.0f);

	for (GLint col = 0; col < 4; col++) {
		for (GLint row = 0; row < 4; row++) {
			GLint i = row + col * 4;
			result.mat[i] = (mat[0 + col * 4] * b.mat[row + 0 * 4])
				+ (mat[1 + col * 4] * b.mat[row + 1 * 4])
				+ (mat[2 + col * 4] * b.mat[row + 2 * 4])
				+ (mat[3 + col * 4] * b.mat[row + 3 * 4]);
		}
	}
	return result;
}