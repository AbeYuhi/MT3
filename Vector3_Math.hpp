#pragma once
#include <Novice.h>
#include <math.h>
#include "Vector3.h"
#include "Matrix4x4.h"

static const int kColumnWidth = 60;
static const int kRowHeight = 20;

Vector3 Add(const Vector3& v1, const Vector3& v2);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Vector3 Multiply(float scalar, const Vector3& v);

float Dot(const Vector3& v1, const Vector3& v2);

float Length(const Vector3& v);

Vector3 Normalize(const Vector3& v1);

Vector3 Cross(const Vector3& v1, const Vector3& v2);

bool IsFront(const Vector3& v1, const Vector3 obj[3]);

Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Vector3 Perpendicular(const Vector3& v);

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

void DrawLine(const Line& line, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawLine(const Ray& ray, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawLine(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);