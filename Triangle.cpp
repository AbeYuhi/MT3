#include "Triangle.h"
#include "Plane.h"
#include "Vector3_Math.hpp"

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Segment line1;
	line1.origin = triangle.vertices[0];
	line1.diff = triangle.vertices[1] - triangle.vertices[0];
	Segment line2;
	line2.origin = triangle.vertices[1];
	line2.diff = triangle.vertices[2] - triangle.vertices[1];	
	Segment line3;
	line3.origin = triangle.vertices[2];
	line3.diff = triangle.vertices[0] - triangle.vertices[2];

	DrawLine(line1, viewProjectionMatrix, viewportMatrix, color);
	DrawLine(line2, viewProjectionMatrix, viewportMatrix, color);
	DrawLine(line3, viewProjectionMatrix, viewportMatrix, color);
}

bool IsCollision(const Triangle& triangle, const Segment& segment) {
	Plane plane = CalculatePlane(triangle);

	if (!IsCollision(segment, plane)) {
		return false;
	}

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / Dot(segment.diff, plane.normal);
	if (t < 0 && 1 < t) {
		return false;
	}

	Vector3 p = segment.origin + (segment.diff * t);

	Vector3 cross1 = Cross(triangle.vertices[1] - triangle.vertices[0], p - triangle.vertices[1]);
	Vector3 cross2 = Cross(triangle.vertices[2] - triangle.vertices[1], p - triangle.vertices[2]);
	Vector3 cross3 = Cross(triangle.vertices[0] - triangle.vertices[2], p - triangle.vertices[0]);

	if (Dot(cross1, plane.normal) >= 0.0f &&
		Dot(cross2, plane.normal) >= 0.0f &&
		Dot(cross3, plane.normal) >= 0.0f) {

		return true;
	}

	return false;
}