#include "Bezier.h"
#include "Vector3_Math.hpp"

Vector3 Leap(const Vector3& v1, const Vector3& v2, float t) {
	return v1 + (v2 - v1) * t;
}


void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const int kSegmentCount = 128;
	Vector3 p[kSegmentCount] = { 0 };
	for (int i = 0; i < kSegmentCount; i++) {
		float t = float(i) / float(kSegmentCount - 1);
		Vector3 p0p1 = Leap(controlPoint0, controlPoint1, t);
		Vector3 p1p2 = Leap(controlPoint1, controlPoint2, t);
		p[i] = Leap(p0p1, p1p2, t);
	}

	for (int i = 0; i < kSegmentCount - 1; i++) {
		Segment pLine;
		pLine.origin = p[i];
		pLine.diff = p[i + 1] - p[i];

		DrawLine(pLine, viewProjectionMatrix, viewportMatrix, color);
	}
}