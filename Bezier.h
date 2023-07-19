#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

Vector3 Leap(const Vector3& v1, const Vector3& v2, float t);

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);