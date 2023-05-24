#include "Grid.h"

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;											//Gridの半分の幅
	const uint32_t kSubdivision = 10;											//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float (kSubdivision);	//1つ分の長さ

	//奥から手前への線を順に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, float(5 - int(xIndex)) * kGridEvery });

		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

		Vector3 localVertices[2] = { {-2, 0, 0}, {2, 0, 0} };
		Vector3 screenVertices[2]{};
		for (uint32_t i = 0; i < 2; ++i) {
			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertex = Transform(localVertices[i], worldViewProjectionMatrix);
			//viewport変換を使ってScreen空間へ
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
		if (xIndex != 5) {
			Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y, 0xAAAAAAFF);
		}
		else {
			Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y, 0x222222FF);
		}
	}
	//左からも線を引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { float(5 - int(zIndex)) * kGridEvery, 0.0f, 0.0f });

		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

		Vector3 localVertices[2] = { {0, 0, -2}, {0, 0, 2} };
		Vector3 screenVertices[2]{};
		for (uint32_t i = 0; i < 2; ++i) {
			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertex = Transform(localVertices[i], worldViewProjectionMatrix);
			//viewport変換を使ってScreen空間へ
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
		if (zIndex != 5) {
			Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y, 0xAAAAAAFF);
		}
		else {
			Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y, 0x222222FF);
		}
	}
}