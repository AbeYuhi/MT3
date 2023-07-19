#include "Bezier.h"
#include "Vector3_Math.hpp"

Vector3 Leap(const Vector3& v1, const Vector3& v2, float t) {
	return v1 + (v2 - v1) * t;
}

Vector3 CatmullRom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t) {
	Vector3 p;

	p.x = 1.0f / 2.0f * (((-1.0f * p0.x) + 3.0f * p1.x - (3.0f * p2.x) + p3.x) * powf(t, 3) + (2.0f * p0.x - (5.0f * p1.x) + 4.0f * p2.x - p3.x) * powf(t, 2) + (-1.0f * p0.x + p2.x) * t + 2.0f * p1.x);
	p.y = 1.0f / 2.0f * (((-1.0f * p0.y) + 3.0f * p1.y - (3.0f * p2.y) + p3.y) * powf(t, 3) + (2.0f * p0.y - (5.0f * p1.y) + 4.0f * p2.y - p3.y) * powf(t, 2) + (-1.0f * p0.y + p2.y) * t + 2.0f * p1.y);
	p.z = 1.0f / 2.0f * (((-1.0f * p0.z) + 3.0f * p1.z - (3.0f * p2.z) + p3.z) * powf(t, 3) + (2.0f * p0.z - (5.0f * p1.z) + 4.0f * p2.z - p3.z) * powf(t, 2) + (-1.0f * p0.z + p2.z) * t + 2.0f * p1.z);

	return p;
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

void DrawCatmullRom(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Vector3& controlPoint3, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const int kSegmentCount = 128;
	Vector3 p[kSegmentCount] = { 0 };
	for (int i = 0; i < kSegmentCount; i++) {
		float t = float(i) / float(kSegmentCount - 1);
		auto movedRate = 1.0f / 3.0f;
		auto section = int(t / movedRate);

		float sectionT = t / movedRate;
		sectionT -= int(sectionT);

		if (section == 0) {
			p[i] = CatmullRom(controlPoint0, controlPoint0, controlPoint1, controlPoint2, sectionT);
		}
		else if (section == 1) {
			p[i] = CatmullRom(controlPoint0, controlPoint1, controlPoint2, controlPoint3, sectionT);
		}
		else if (section == 2) {
			p[i] = CatmullRom(controlPoint1, controlPoint2, controlPoint3, controlPoint3, sectionT);
		}
		else {
			p[i] = controlPoint3;
		}
	}

	for (int i = 0; i < kSegmentCount - 1; i++) {
		Segment pLine;
		pLine.origin = p[i];
		pLine.diff = p[i + 1] - p[i];

		DrawLine(pLine, viewProjectionMatrix, viewportMatrix, color);
	}
}