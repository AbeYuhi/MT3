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
#include "Bezier.h"
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

	Vector3 controlPoints[3] = {
		{-0.8f, 0.58f, 1.0f},
		{1.76f, 1.0f, -0.3f},
		{0.94f, -0.7f, 2.3f},
	};


	Sphere controlPointSpheres[3];

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
		ImGui::SliderFloat3("controlPoint0", &controlPoints[0].x, -2, 2);
		ImGui::SliderFloat3("controlPoint1", &controlPoints[1].x, -2, 2);
		ImGui::SliderFloat3("controlPoint2", &controlPoints[2].x, -2, 2);
		ImGui::End();

		controlPointSpheres[0].center = controlPoints[0];
		controlPointSpheres[0].radius = 0.05f;
		controlPointSpheres[1].center = controlPoints[1];
		controlPointSpheres[1].radius = 0.05f;
		controlPointSpheres[2].center = controlPoints[2];
		controlPointSpheres[2].radius = 0.05f;

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

		for (int i = 0; i < 3; i++) {
			DrawSphere(controlPointSpheres[i], viewProjectionMatrix, viewportMatrix, BLACK);
		}

		DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], viewProjectionMatrix, viewportMatrix, WHITE);

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
