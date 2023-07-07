#pragma once
#include "Vector3.h"
#include "Sphere.h"
#include "Matrix4x4.h"

struct OBB
{
	Vector3 center;
	Vector3 orientations[3];
	Vector3 size;
};

bool IsCollision(const OBB& obb, const Sphere& sphere);

void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

