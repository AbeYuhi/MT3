#include <Novice.h>
#include <ImGuiManager.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector3_Math.hpp"
#include "Matrix4x4.h"
#include "Grid.h"
#include "Sphere.h"
#define M_PI 3.14f

const char kWindowTitle[] = "LE2A_02_アベユウヒ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = { 0 };

	Vector3 cameraTranslate{0.0f, 1.9f, -6.49f};
	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};

	/*Sphere sphere;

	sphere.center = { 0.0f, 0.0f, 0.0f};
	sphere.radius = 1.0f;*/

	Segment segment{ {-2.0f, -1.0f, 0.0f}, {3.0f, 2.0f, 2.0f} };
	Vector3 point{-1.5f, 0.6f, 0.6f};

	Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = ClosestPoint(point, segment);

	Vector2Int mousePos{};
	Vector2Int preMousePos{};

	/*Vector3 cameraTranslate{0.0f, 10, 0.0f};
	Vector3 cameraRotate{0.5f * 3.14f, 0.0f, 0.0f};*/

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
		
		preMousePos = mousePos;
		Novice::GetMousePosition(&mousePos.x, &mousePos.y);

		if (Novice::IsPressMouse(1)) {
			Vector2Int mouseAmount = mousePos - preMousePos;

			cameraRotate.x += mouseAmount.y * 0.02f;
			cameraRotate.y += mouseAmount.x * 0.02f;
		}

		if (keys[DIK_A]) {
			cameraTranslate.x -= 0.5f;
		}
		if (keys[DIK_D]) {
			cameraTranslate.x += 0.5f;
		}
		if (keys[DIK_W]) {
			cameraTranslate.z += 0.5f;
		}
		if (keys[DIK_S]) {
			cameraTranslate.z -= 0.5f;
		}


		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);

		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

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

		ImGui::Begin("CameraManager");
		float* inputCameraTranslate[3] = { &cameraTranslate.x, &cameraTranslate.y, &cameraTranslate.z };
		float* inputCameraRotate[3] = { &cameraRotate.x, &cameraRotate.y, &cameraRotate.z };
		ImGui::SliderFloat3("CameraTranslate", *inputCameraTranslate, -100.0f, 100.0f);
		ImGui::SliderFloat3("CameraRotate", *inputCameraRotate, -2.0f * M_PI, 2.0f * M_PI);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		Sphere pointSphere{ point, 0.01f };
		Sphere closestPointSphere{closestPoint, 0.01f};
		DrawSphere(pointSphere, viewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(closestPointSphere, viewProjectionMatrix, viewportMatrix, BLACK);

		Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);
		Novice::DrawLine(
			int(start.x), int(start.y),
			int(end.x), int(end.y),
			WHITE
		);



		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
