#include "AABB.h"

void ControlMinMax(AABB& a) {
	a.min.x = (std::min)(a.min.x, a.max.x);
	a.max.x = (std::max)(a.min.x, a.max.x);

	a.min.y = (std::min)(a.min.y, a.max.y);
	a.max.y = (std::max)(a.min.y, a.max.y);

	a.min.z = (std::min)(a.min.z, a.max.z);
	a.max.z = (std::max)(a.min.z, a.max.z);
}

bool IsCollision(const AABB& a, const AABB& b) {
	if (a.min.x <= b.max.x && a.max.x >= b.min.x &&
		a.min.y <= b.max.y && a.max.y >= b.min.y &&
		a.min.z <= b.max.z && a.max.z >= b.min.z) {
		return true;
	}
	return false;
}

bool IsCollision(const AABB& aabb, const Segment& segment) {
	float tMinX = (aabb.min.x - segment.origin.x) / segment.diff.x;
	float tMaxX = (aabb.max.x - segment.origin.x) / segment.diff.x;
	float tNearX = min(tMinX, tMaxX);
	float tFarX = max(tMinX, tMaxX);

	float tMinY = (aabb.min.y - segment.origin.y) / segment.diff.y;
	float tMaxY = (aabb.max.y - segment.origin.y) / segment.diff.y;
	float tNearY = min(tMinY, tMaxY);
	float tFarY = max(tMinY, tMaxY);

	float tMinZ = (aabb.min.z - segment.origin.z) / segment.diff.z;
	float tMaxZ = (aabb.max.z - segment.origin.z) / segment.diff.z;
	float tNearZ = min(tMinZ, tMaxZ);
	float tFarZ = max(tMinZ, tMaxZ);

	float tmin = max(max(tNearX, tNearY), tNearZ);
	float tmax = min(min(tFarX, tFarY), tFarZ);

	if (tmin <= tmax) {

		if (tmin <= 1.0f && 0.0f <= tmax) {
			return true;
		}
	}
	return false;
}

bool IsCollision(const AABB& aabb, const Ray& ray) {
	float tMinX = (aabb.min.x - ray.origin.x) / ray.diff.x;
	float tMaxX = (aabb.max.x - ray.origin.x) / ray.diff.x;
	float tNearX = min(tMinX, tMaxX);
	float tFarX = max(tMinX, tMaxX);

	float tMinY = (aabb.min.y - ray.origin.y) / ray.diff.y;
	float tMaxY = (aabb.max.y - ray.origin.y) / ray.diff.y;
	float tNearY = min(tMinY, tMaxY);
	float tFarY = max(tMinY, tMaxY);

	float tMinZ = (aabb.min.z - ray.origin.z) / ray.diff.z;
	float tMaxZ = (aabb.max.z - ray.origin.z) / ray.diff.z;
	float tNearZ = min(tMinZ, tMaxZ);
	float tFarZ = max(tMinZ, tMaxZ);

	float tmin = max(max(tNearX, tNearY), tNearZ);
	float tmax = min(min(tFarX, tFarY), tFarZ);

	if (tmin <= tmax) {

		if (0.0f <= tmax) {
			return true;
		}
	}
	return false;
}

bool IsCollision(const AABB& aabb, const Line& line) {
	float tMinX = (aabb.min.x - line.origin.x) / line.diff.x;
	float tMaxX = (aabb.max.x - line.origin.x) / line.diff.x;
	float tNearX = min(tMinX, tMaxX);
	float tFarX = max(tMinX, tMaxX);

	float tMinY = (aabb.min.y - line.origin.y) / line.diff.y;
	float tMaxY = (aabb.max.y - line.origin.y) / line.diff.y;
	float tNearY = min(tMinY, tMaxY);
	float tFarY = max(tMinY, tMaxY);

	float tMinZ = (aabb.min.z - line.origin.z) / line.diff.z;
	float tMaxZ = (aabb.max.z - line.origin.z) / line.diff.z;
	float tNearZ = min(tMinZ, tMaxZ);
	float tFarZ = max(tMinZ, tMaxZ);

	float tmin = max(max(tNearX, tNearY), tNearZ);
	float tmax = min(min(tFarX, tFarY), tFarZ);

	if (tmin <= tmax) {
		return true;
	}
	return false;
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 point[8];

	point[0] = {aabb.min.x, aabb.min.y, aabb.min.z};

	point[1] = { aabb.max.x, aabb.min.y, aabb.min.z };

	point[2] = { aabb.min.x, aabb.max.y, aabb.min.z };

	point[3] = { aabb.min.x, aabb.min.y, aabb.max.z };

	point[4] = { aabb.max.x, aabb.max.y, aabb.min.z };

	point[5] = { aabb.max.x, aabb.min.y, aabb.max.z };

	point[6] = { aabb.min.x, aabb.max.y, aabb.max.z };

	point[7] = { aabb.max.x, aabb.max.y, aabb.max.z };

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