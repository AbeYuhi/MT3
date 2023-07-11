#include <Novice.h>
#include <ImGuiManager.h>
#include <memory>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector3_Math.hpp"
#include "Matrix4x4.h"
#include "Grid.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "AABB.h"
#include "OBB.h"
#include "Camera.h"
#define M_PI 3.14f

const char kWindowTitle[] = "LE2A_02_アベユウヒ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	OBB obb1{
		.center{0.0f, 0.0f, 0.0f},
		.orientations{{1.0f, 0.0f, 0.0f},
					  {0.0f, 1.0f, 0.0f},
					  {0.0f, 0.0f, 1.0f}},
		.size{0.83f, 0.26f, 0.24f}
	};
	unsigned int obbColor = WHITE;
	Vector3 rotateObb1 = { 0.0f, 0.0f, 0.0f };

	OBB obb2{
		.center{0.9f, 0.66f, 0.78f},
		.orientations{{1.0f, 0.0f, 0.0f},
					  {0.0f, 1.0f, 0.0f},
					  {0.0f, 0.0f, 1.0f}},
		.size{0.5f, 0.37f, 0.5f}
	};
	Vector3 rotateObb2 = { 0.0f, 0.0f, 0.0f };

	std::unique_ptr<Camera> camera(new Camera(), std::default_delete<Camera>());
	camera->Initialize();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		ImGui::Begin("Window");
		ImGui::SliderFloat3("OBB1center", &obb1.center.x, -5, 5);
		ImGui::SliderFloat3("OBB1rotate", &rotateObb1.x, -2 * M_PI, 2 * M_PI);
		ImGui::SliderFloat3("OBB1size", &obb1.size.x, 0, 5);
		ImGui::SliderFloat3("OBB2center", &obb2.center.x, -5, 5);
		ImGui::SliderFloat3("OBB2rotate", &rotateObb2.x, -2 * M_PI, 2 * M_PI);
		ImGui::SliderFloat3("OBB2size", &obb2.size.x, 0, 5);
		ImGui::End();
		Matrix4x4 rotate1Matrix = MakeRotateMatrix(rotateObb1);
		obb1.orientations[0].x = rotate1Matrix.m[0][0];
		obb1.orientations[0].y = rotate1Matrix.m[0][1];
		obb1.orientations[0].z = rotate1Matrix.m[0][2];

		obb1.orientations[1].x = rotate1Matrix.m[1][0];
		obb1.orientations[1].y = rotate1Matrix.m[1][1];
		obb1.orientations[1].z = rotate1Matrix.m[1][2];

		obb1.orientations[2].x = rotate1Matrix.m[2][0];
		obb1.orientations[2].y = rotate1Matrix.m[2][1];
		obb1.orientations[2].z = rotate1Matrix.m[2][2];

		Matrix4x4 rotate2Matrix = MakeRotateMatrix(rotateObb2);
		obb2.orientations[0].x = rotate2Matrix.m[0][0];
		obb2.orientations[0].y = rotate2Matrix.m[0][1];
		obb2.orientations[0].z = rotate2Matrix.m[0][2];

		obb2.orientations[1].x = rotate2Matrix.m[1][0];
		obb2.orientations[1].y = rotate2Matrix.m[1][1];
		obb2.orientations[1].z = rotate2Matrix.m[1][2];

		obb2.orientations[2].x = rotate2Matrix.m[2][0];
		obb2.orientations[2].y = rotate2Matrix.m[2][1];
		obb2.orientations[2].z = rotate2Matrix.m[2][2];

		if (IsCollision(obb1, obb2)) {
			obbColor = RED;
		}
		else {
			obbColor = WHITE;
		}


		camera->Update(keys);

		Matrix4x4 viewMatrix = Inverse(camera->GetWorldTransform());

		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);

		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		//ViewportMatrixを作る
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawOBB(obb1, viewProjectionMatrix, viewportMatrix, obbColor);
		DrawOBB(obb2, viewProjectionMatrix, viewportMatrix, WHITE);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	};

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
