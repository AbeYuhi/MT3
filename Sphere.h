#pragma once
#include <Novice.h>
#include <math.h>
#include "Vector3.h"
#include "Vector3_Math.hpp"
#include "Vector2.h"
#include "Matrix4x4.h"

struct Sphere {
	Vector3 center;
	float radius;
};

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color, uint32_t texture, Vector2Int textureSIze);

bool IsCollision(const Sphere& s1, const Sphere& s2);
