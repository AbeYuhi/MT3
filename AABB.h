#pragma once
#include"Vector3.h"
#include"Vector3_Math.hpp"

struct AABB {
	Vector3 min;
	Vector3 max;
};

void ControlMinMax(AABB& a);

bool IsCollision(const AABB& a, const AABB& b);

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);