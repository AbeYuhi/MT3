#pragma once

struct Matrix4x4 {
	float m[4][4];
};

Matrix4x4 Add(Matrix4x4 matrix1, Matrix4x4 matrix2);

Matrix4x4 Subtract(Matrix4x4 matrix1, Matrix4x4 matrix2);

Matrix4x4 Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2);

float Det(Matrix4x4 matrix);

Matrix4x4 Inverse(Matrix4x4 matrix);

Matrix4x4 Transpose(Matrix4x4 matrix);

Matrix4x4 MakeIdentity4x4();

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);