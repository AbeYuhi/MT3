#include "Sphere.h"
#define M_PI 3.14f


void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 16;
	const float kLonEvery = (2 * M_PI) / kSubdivision;
	const float kLatEvery = (M_PI) / kSubdivision;
	//緯度の方向に分割 -π/1 ～ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -M_PI / 2.0f + kLatEvery * latIndex; //現在の緯度
		//経度の方向に分割 0～2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			//world座標系でのa, b, cを求める
			Vector3 a, b, c;
			a = { std::cos(lat) * std::cos(lon),
				std::sin(lat),
				std::cos(lat) * std::sin(lon)};

			b = { std::cos(lat + kLatEvery) * std::cos(lon),
				std::sin(lat + kLatEvery),
				std::cos(lat + kLatEvery) * std::sin(lon) };

			c = { std::cos(lat) * std::cos(lon + kLonEvery),
				std::sin(lat),
				std::cos(lat) * std::sin(lon + kLonEvery)};

			a *= sphere.radius;
			b *= sphere.radius;
			c *= sphere.radius;

			a += sphere.center;
			b += sphere.center;
			c += sphere.center;

			Matrix4x4 worldMatrixA = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, a);

			Matrix4x4 worldViewProjectionMatrixA = Multiply(worldMatrixA, viewProjectionMatrix);

			Matrix4x4 worldMatrixB = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, b);

			Matrix4x4 worldViewProjectionMatrixB = Multiply(worldMatrixB, viewProjectionMatrix);

			Matrix4x4 worldMatrixC = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, c);

			Matrix4x4 worldViewProjectionMatrixC = Multiply(worldMatrixC, viewProjectionMatrix);

			Vector3 screenVertices[3]{};
			
			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertexA = Transform({ 0, 0, 0 }, worldViewProjectionMatrixA);
			//viewport変換を使ってScreen空間へ
			screenVertices[0] = Transform(ndcVertexA, viewportMatrix);

			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertexB = Transform({ 0, 0, 0 }, worldViewProjectionMatrixB);
			//viewport変換を使ってScreen空間へ
			screenVertices[1] = Transform(ndcVertexB, viewportMatrix);

			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertexC = Transform({ 0, 0, 0 }, worldViewProjectionMatrixC);
			//viewport変換を使ってScreen空間へ
			screenVertices[2] = Transform(ndcVertexC, viewportMatrix);

			Novice::DrawLine(
				(int)screenVertices[0].x, (int)screenVertices[0].y,
				(int)screenVertices[1].x, (int)screenVertices[1].y,
				color);

			Novice::DrawLine(
				(int)screenVertices[0].x, (int)screenVertices[0].y,
				(int)screenVertices[2].x, (int)screenVertices[2].y,
				color);
		}
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color, uint32_t texture, Vector2Int textureSIze) {
	const uint32_t kSubdivision = 16;
	const float kLonEvery = (2 * M_PI) / kSubdivision;
	const float kLatEvery = (M_PI) / kSubdivision;
	//緯度の方向に分割 -π/1 ～ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -M_PI / 2.0f + kLatEvery * latIndex; //現在の緯度
		//経度の方向に分割 0～2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			//world座標系でのa, b, cを求める
			Vector3 a, b, c, d;
			a = { std::cos(lat) * std::cos(lon),
				std::sin(lat),
				std::cos(lat) * std::sin(lon) };

			b = { std::cos(lat + kLatEvery) * std::cos(lon),
				std::sin(lat + kLatEvery),
				std::cos(lat + kLatEvery) * std::sin(lon) };

			c = { std::cos(lat) * std::cos(lon + kLonEvery),
				std::sin(lat),
				std::cos(lat) * std::sin(lon + kLonEvery) };

			d = { std::cos(lat + kLatEvery) * std::cos(lon + kLonEvery),
				std::sin(lat + kLatEvery),
				std::cos(lat + kLatEvery) * std::sin(lon + kLonEvery) };

			a *= sphere.radius;
			b *= sphere.radius;
			c *= sphere.radius;
			d *= sphere.radius;

			a += sphere.center;
			b += sphere.center;
			c += sphere.center;
			d += sphere.center;

			Matrix4x4 worldMatrixA = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, a);

			Matrix4x4 worldViewProjectionMatrixA = Multiply(worldMatrixA, viewProjectionMatrix);

			Matrix4x4 worldMatrixB = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, b);

			Matrix4x4 worldViewProjectionMatrixB = Multiply(worldMatrixB, viewProjectionMatrix);

			Matrix4x4 worldMatrixC = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, c);

			Matrix4x4 worldViewProjectionMatrixC = Multiply(worldMatrixC, viewProjectionMatrix);

			Matrix4x4 worldMatrixD = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, d);

			Matrix4x4 worldViewProjectionMatrixD = Multiply(worldMatrixD, viewProjectionMatrix);

			Vector3 screenVertices[4]{};

			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertexA = Transform({ 0, 0, 0 }, worldViewProjectionMatrixA);
			//viewport変換を使ってScreen空間へ
			screenVertices[0] = Transform(ndcVertexA, viewportMatrix);

			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertexB = Transform({ 0, 0, 0 }, worldViewProjectionMatrixB);
			//viewport変換を使ってScreen空間へ
			screenVertices[1] = Transform(ndcVertexB, viewportMatrix);

			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertexC = Transform({ 0, 0, 0 }, worldViewProjectionMatrixC);
			//viewport変換を使ってScreen空間へ
			screenVertices[2] = Transform(ndcVertexC, viewportMatrix);

			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertexD = Transform({ 0, 0, 0 }, worldViewProjectionMatrixD);
			//viewport変換を使ってScreen空間へ
			screenVertices[3] = Transform(ndcVertexD, viewportMatrix);

			float u = float(lonIndex) / float(kSubdivision);
			float v = float(latIndex) / float(kSubdivision);
			/*int uSize = static_cast<int>(1.0f / float(kSubdivision));
			int vSize = static_cast<int>(1.0f / float(kSubdivision));*/

			Vector2Int uvConversion = UVConversion(textureSIze, u, v);

			Novice::DrawQuad(
				static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
				static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
				static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
				static_cast<int>(screenVertices[3].x), static_cast<int>(screenVertices[3].y),
				uvConversion.x, uvConversion.y, uSize, vSize, texture, color
			);
		}
	}
}

bool IsCollision(const Sphere& s1, const Sphere& s2) {
	auto distance = Length(s2.center - s1.center);

	if (distance <= s1.radius + s2.radius) {
		return true;
	}

	return false;
}