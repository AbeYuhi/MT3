#include "OBB.h"
#include "Vector3_Math.hpp"
#include "Sphere.h"

bool IsCollision(const OBB& obb, const Sphere& sphere) {
	Matrix4x4 worldMatrix = MakeIdentity4x4();
	worldMatrix.m[0][0] = obb.orientations[0].x;
	worldMatrix.m[0][1] = obb.orientations[0].y;
	worldMatrix.m[0][2] = obb.orientations[0].z;

	worldMatrix.m[1][0] = obb.orientations[1].x;
	worldMatrix.m[1][1] = obb.orientations[1].y;
	worldMatrix.m[1][2] = obb.orientations[1].z;

	worldMatrix.m[2][0] = obb.orientations[2].x;
	worldMatrix.m[2][1] = obb.orientations[2].y;
	worldMatrix.m[2][2] = obb.orientations[2].z;

	worldMatrix.m[3][0] = obb.center.x;
	worldMatrix.m[3][1] = obb.center.y;
	worldMatrix.m[3][2] = obb.center.z;

	Matrix4x4 worldMatrixInverse = Inverse(worldMatrix);
	Vector3 centerInOBBLocalSpace = Transform(sphere.center, worldMatrixInverse);
	AABB aabbLocal{ .min = {-obb.size.x, -obb.size.y, -obb.size.z}, .max{obb.size.x, obb.size.y, obb.size.z} };
	Sphere sphereOBBLocal{ .center = centerInOBBLocalSpace, .radius = sphere.radius };
	if (IsCollision(sphereOBBLocal, aabbLocal)) {
		return true;
	}
	return false;
}

void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 point[8];

	point[0] = { -obb.size.x, -obb.size.y, -obb.size.z };

	point[1] = { +obb.size.x, -obb.size.y, -obb.size.z };

	point[2] = { -obb.size.x, +obb.size.y, -obb.size.z };

	point[3] = { -obb.size.x, -obb.size.y, +obb.size.z };

	point[4] = { +obb.size.x, +obb.size.y, -obb.size.z };

	point[5] = { +obb.size.x, -obb.size.y, +obb.size.z };

	point[6] = { -obb.size.x, +obb.size.y, +obb.size.z };

	point[7] = { +obb.size.x, +obb.size.y, +obb.size.z };

	Matrix4x4 rotateMatrix = MakeIdentity4x4();
	rotateMatrix.m[0][0] = obb.orientations[0].x;
	rotateMatrix.m[0][1] = obb.orientations[0].y;
	rotateMatrix.m[0][2] = obb.orientations[0].z;

	rotateMatrix.m[1][0] = obb.orientations[1].x;
	rotateMatrix.m[1][1] = obb.orientations[1].y;
	rotateMatrix.m[1][2] = obb.orientations[1].z;

	rotateMatrix.m[2][0] = obb.orientations[2].x;
	rotateMatrix.m[2][1] = obb.orientations[2].y;
	rotateMatrix.m[2][2] = obb.orientations[2].z;

	for (int i = 0; i < 8; i++) {
		point[i] = Transform(point[i], rotateMatrix);
		point[i].x += obb.center.x;
		point[i].y += obb.center.y;
		point[i].z += obb.center.z;
	}

	Segment segment[12] = { 0 };
	segment[0].origin = point[0];
	segment[0].diff = point[1] - point[0];
	segment[1].origin = point[2];
	segment[1].diff = point[4] - point[2];
	segment[2].origin = point[3];
	segment[2].diff = point[5] - point[3];
	segment[3].origin = point[6];
	segment[3].diff = point[7] - point[6];

	segment[4].origin = point[0];
	segment[4].diff = point[3] - point[0];
	segment[5].origin = point[1];
	segment[5].diff = point[5] - point[1];
	segment[6].origin = point[2];
	segment[6].diff = point[6] - point[2];
	segment[7].origin = point[4];
	segment[7].diff = point[7] - point[4];

	segment[8].origin = point[0];
	segment[8].diff = point[2] - point[0];
	segment[9].origin = point[1];
	segment[9].diff = point[4] - point[1];
	segment[10].origin = point[3];
	segment[10].diff = point[6] - point[3];
	segment[11].origin = point[5];
	segment[11].diff = point[7] - point[5];

	for (int i = 0; i < 12; i++) {
		DrawLine(segment[i], viewProjectionMatrix, viewportMatrix, color);
	}
}