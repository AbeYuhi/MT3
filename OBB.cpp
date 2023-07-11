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

bool IsCollision(const OBB& obb, const Segment& segment) {
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
	Vector3 startOBBLocal = Transform(segment.origin, worldMatrixInverse);
	Vector3 endOBBLocal = Transform(segment.origin + segment.diff, worldMatrixInverse);
	AABB aabbLocal{ .min = {-obb.size.x, -obb.size.y, -obb.size.z}, .max{obb.size.x, obb.size.y, obb.size.z} };
	Segment segmentOBBLocal{ .origin{startOBBLocal}, .diff{endOBBLocal - startOBBLocal} };
	if (IsCollision(aabbLocal, segmentOBBLocal)) {
		return true;
	}
	return false;
}

bool IsCollision(const OBB& obb, const Ray& ray) {
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
	Vector3 startOBBLocal = Transform(ray.origin, worldMatrixInverse);
	Vector3 endOBBLocal = Transform(ray.origin + ray.diff, worldMatrixInverse);
	AABB aabbLocal{ .min = {-obb.size.x, -obb.size.y, -obb.size.z}, .max{obb.size.x, obb.size.y, obb.size.z} };
	Ray segmentOBBLocal{ .origin{startOBBLocal}, .diff{endOBBLocal - startOBBLocal} };
	if (IsCollision(aabbLocal, segmentOBBLocal)) {
		return true;
	}
	return false;
}

bool IsCollision(const OBB& obb, const Line& line) {
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
	Vector3 startOBBLocal = Transform(line.origin, worldMatrixInverse);
	Vector3 endOBBLocal = Transform(line.origin + line.diff, worldMatrixInverse);
	AABB aabbLocal{ .min = {-obb.size.x, -obb.size.y, -obb.size.z}, .max{obb.size.x, obb.size.y, obb.size.z} };
	Line segmentOBBLocal{ .origin{startOBBLocal}, .diff{endOBBLocal - startOBBLocal} };
	if (IsCollision(aabbLocal, segmentOBBLocal)) {
		return true;
	}
	return false;
}

bool IsCollision(const OBB& obb1, const OBB& obb2) {
	Vector3 separationAxis[15];

	Matrix4x4 rotate1Matrix = MakeIdentity4x4();
	rotate1Matrix.m[0][0] = obb1.orientations[0].x;
	rotate1Matrix.m[0][1] = obb1.orientations[0].y;
	rotate1Matrix.m[0][2] = obb1.orientations[0].z;

	rotate1Matrix.m[1][0] = obb1.orientations[1].x;
	rotate1Matrix.m[1][1] = obb1.orientations[1].y;
	rotate1Matrix.m[1][2] = obb1.orientations[1].z;

	rotate1Matrix.m[2][0] = obb1.orientations[2].x;
	rotate1Matrix.m[2][1] = obb1.orientations[2].y;
	rotate1Matrix.m[2][2] = obb1.orientations[2].z;

	rotate1Matrix.m[3][0] = obb1.center.x;
	rotate1Matrix.m[3][1] = obb1.center.y;
	rotate1Matrix.m[3][2] = obb1.center.z;

	Matrix4x4 rotate2Matrix = MakeIdentity4x4();
	rotate2Matrix.m[0][0] = obb2.orientations[0].x;
	rotate2Matrix.m[0][2] = obb2.orientations[0].y;
	rotate2Matrix.m[0][2] = obb2.orientations[0].z;

	rotate2Matrix.m[2][0] = obb2.orientations[2].x;
	rotate2Matrix.m[2][2] = obb2.orientations[2].y;
	rotate2Matrix.m[2][2] = obb2.orientations[2].z;

	rotate2Matrix.m[2][0] = obb2.orientations[2].x;
	rotate2Matrix.m[2][2] = obb2.orientations[2].y;
	rotate2Matrix.m[2][2] = obb2.orientations[2].z;

	rotate2Matrix.m[3][0] = obb2.center.x;
	rotate2Matrix.m[3][2] = obb2.center.y;
	rotate2Matrix.m[3][2] = obb2.center.z;

	Vector3 point1[8];

	point1[0] = { -obb1.size.x, -obb1.size.y, -obb1.size.z };

	point1[1] = { +obb1.size.x, -obb1.size.y, -obb1.size.z };

	point1[2] = { -obb1.size.x, +obb1.size.y, -obb1.size.z };

	point1[3] = { -obb1.size.x, -obb1.size.y, +obb1.size.z };

	point1[4] = { +obb1.size.x, +obb1.size.y, -obb1.size.z };

	point1[5] = { +obb1.size.x, -obb1.size.y, +obb1.size.z };

	point1[6] = { -obb1.size.x, +obb1.size.y, +obb1.size.z };

	point1[7] = { +obb1.size.x, +obb1.size.y, +obb1.size.z };

	for (int i = 0; i < 8; i++) {
		point1[i] = Transform(point1[i], rotate1Matrix);
	}

	Vector3 point2[8];

	point2[0] = { -obb2.size.x, -obb2.size.y, -obb2.size.z };

	point2[1] = { +obb2.size.x, -obb2.size.y, -obb2.size.z };

	point2[2] = { -obb2.size.x, +obb2.size.y, -obb2.size.z };

	point2[3] = { -obb2.size.x, -obb2.size.y, +obb2.size.z };

	point2[4] = { +obb2.size.x, +obb2.size.y, -obb2.size.z };

	point2[5] = { +obb2.size.x, -obb2.size.y, +obb2.size.z };

	point2[6] = { -obb2.size.x, +obb2.size.y, +obb2.size.z };

	point2[7] = { +obb2.size.x, +obb2.size.y, +obb2.size.z };

	for (int i = 0; i < 8; i++) {
		point2[i] = Transform(point2[i], rotate2Matrix);
	}

	separationAxis[0] = Transform({ 1.0f, 0.0f, 0.0f }, rotate1Matrix);
	separationAxis[1] = Transform({ 0.0f, 1.0f, 0.0f }, rotate1Matrix);
	separationAxis[2] = Transform({ 0.0f, 0.0f, 1.0f }, rotate1Matrix);
	separationAxis[3] = Transform({ 1.0f, 0.0f, 0.0f }, rotate2Matrix);
	separationAxis[4] = Transform({ 0.0f, 1.0f, 0.0f }, rotate2Matrix);
	separationAxis[5] = Transform({ 0.0f, 0.0f, 1.0f }, rotate2Matrix);

	separationAxis[6] = Cross(separationAxis[0], separationAxis[3]);
	separationAxis[7] = Cross(separationAxis[0], separationAxis[4]);
	separationAxis[8] = Cross(separationAxis[0], separationAxis[5]);
	separationAxis[9] = Cross(separationAxis[1], separationAxis[3]);
	separationAxis[10] = Cross(separationAxis[1], separationAxis[4]);
	separationAxis[11] = Cross(separationAxis[1], separationAxis[5]);
	separationAxis[12] = Cross(separationAxis[2], separationAxis[3]);
	separationAxis[13] = Cross(separationAxis[2], separationAxis[4]);
	separationAxis[14] = Cross(separationAxis[2], separationAxis[5]);

	////面法線
	//separationAxis[0] = obb1.orientations[0];
	//separationAxis[1] = obb1.orientations[1];
	//separationAxis[2] = obb1.orientations[2];
	//separationAxis[3] = obb2.orientations[0];
	//separationAxis[4] = obb2.orientations[1];
	//separationAxis[5] = obb2.orientations[2];

	////クロス積
	//separationAxis[6] = Cross(obb1.orientations[0], obb2.orientations[0]);
	//separationAxis[7] = Cross(obb1.orientations[0], obb2.orientations[1]);
	//separationAxis[8] = Cross(obb1.orientations[0], obb2.orientations[2]);
	//separationAxis[9] = Cross(obb1.orientations[1], obb2.orientations[0]);
	//separationAxis[10] = Cross(obb1.orientations[1], obb2.orientations[1]);
	//separationAxis[11] = Cross(obb1.orientations[1], obb2.orientations[2]);
	//separationAxis[12] = Cross(obb1.orientations[2], obb2.orientations[0]);
	//separationAxis[13] = Cross(obb1.orientations[2], obb2.orientations[1]);
	//separationAxis[14] = Cross(obb1.orientations[2], obb2.orientations[2]);


	for (int i = 0; i < 15; i++) {
		float max1 = 0.0f, max2 = 0.0f;
		float min1 = 0.0f, min2 = 0.0f;

		for (int j = 0; j < 8; j++) {
			//一時保存
			float tmp = 0.0f;
			//obb
			tmp = Dot(point1[j], Normalize(separationAxis[i]));
			//2.射影した点の最大値と最小値を求める
			if (j == 0 || min1 > tmp) {
				min1 = tmp;
			}
			if (j == 0 || max1 < tmp) {
				max1 = tmp;
			}

			//obb2
			tmp = Dot(point2[j], Normalize(separationAxis[i]));
			//2.射影した点の最大値と最小値を求める
			if (j == 0 || min2 > tmp) {
				min2 = tmp;
			}
			if (j == 0 || max2 < tmp) {
				max2 = tmp;
			}
		}

		float L1 = max1 - min1;
		float L2 = max2 - min2;

		float sumSpan = L1 + L2;
		float lonSpan = (std::max)(max1, max2) - (std::min)(min1, min2);
		if (sumSpan < lonSpan) {
			return false;
		}
	}
	return true;
}

void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 point1[8];

	point1[0] = { -obb.size.x, -obb.size.y, -obb.size.z };

	point1[1] = { +obb.size.x, -obb.size.y, -obb.size.z };

	point1[2] = { -obb.size.x, +obb.size.y, -obb.size.z };

	point1[3] = { -obb.size.x, -obb.size.y, +obb.size.z };

	point1[4] = { +obb.size.x, +obb.size.y, -obb.size.z };

	point1[5] = { +obb.size.x, -obb.size.y, +obb.size.z };

	point1[6] = { -obb.size.x, +obb.size.y, +obb.size.z };

	point1[7] = { +obb.size.x, +obb.size.y, +obb.size.z };

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

	rotateMatrix.m[3][0] = obb.center.x;
	rotateMatrix.m[3][1] = obb.center.y;
	rotateMatrix.m[3][2] = obb.center.z;

	for (int i = 0; i < 8; i++) {
		point1[i] = Transform(point1[i], rotateMatrix);
	}

	Segment segment[12] = { 0 };
	segment[0].origin = point1[0];
	segment[0].diff = point1[1] - point1[0];
	segment[1].origin = point1[2];
	segment[1].diff = point1[4] - point1[2];
	segment[2].origin = point1[3];
	segment[2].diff = point1[5] - point1[3];
	segment[3].origin = point1[6];
	segment[3].diff = point1[7] - point1[6];

	segment[4].origin = point1[0];
	segment[4].diff = point1[3] - point1[0];
	segment[5].origin = point1[1];
	segment[5].diff = point1[5] - point1[1];
	segment[6].origin = point1[2];
	segment[6].diff = point1[6] - point1[2];
	segment[7].origin = point1[4];
	segment[7].diff = point1[7] - point1[4];

	segment[8].origin = point1[0];
	segment[8].diff = point1[2] - point1[0];
	segment[9].origin = point1[1];
	segment[9].diff = point1[4] - point1[1];
	segment[10].origin = point1[3];
	segment[10].diff = point1[6] - point1[3];
	segment[11].origin = point1[5];
	segment[11].diff = point1[7] - point1[5];

	for (int i = 0; i < 12; i++) {
		DrawLine(segment[i], viewProjectionMatrix, viewportMatrix, color);
	}
}