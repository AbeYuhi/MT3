#pragma once
#include <Novice.h>
#include "Vector3.h"
#include "Vector3_Math.hpp"
#include "Matrix4x4.h"

struct Plane {
	Vector3 normal;
	float distance;
};

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);