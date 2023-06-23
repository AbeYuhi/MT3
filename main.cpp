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

	//uint32_t sphereTexture = Novice::LoadTexture("./Resources/Images/uvChecker.png");

	/*Sphere s1;
	unsigned int s1Color = WHITE;
	s1.center = { 0.0f, 0.0f, -1.0f};
	s1.radius = 1.0f;*/

	AABB aabb1 = {
	.min{-0.5f, -0.5f, -0.5f},
	.max{0.0f, 0.0f, 0.0f}
	};
	uint32_t aabb1color = WHITE;

	Sphere sphere;
	sphere.center = { 1, 1, 1};
	sphere.radius = 1;

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
		ImGui::SliderFloat3("aabb1Min", &aabb1.min.x, -10, 10);
		ImGui::SliderFloat3("aabb1Max", &aabb1.max.x, -10, 10);
		ImGui::SliderFloat3("sphereCenterPos", &sphere.center.x, -10, 10);
		ImGui::SliderFloat("sphereRadius", &sphere.radius , 0, 10);
		ImGui::End();

		ControlMinMax(aabb1);

		if(IsCollision(sphere, aabb1)) {
			aabb1color = RED;
		}
		else {
			aabb1color = WHITE;
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

		DrawAABB(aabb1, viewProjectionMatrix, viewportMatrix, aabb1color);
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, WHITE);

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
