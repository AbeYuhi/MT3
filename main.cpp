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

	Vector3 translates[3] = {
		{0.2f, 1.0f, 0.0f},
		{0.4f, 0.0f, 0.0f},
		{0.3f, 0.0f, 0.0f}
	};

	Vector3 rotates[3] = {
		{0.0f, 0.0f, -6.8f},
		{0.0f, 0.0f, -1.4f},
		{0.0f, 0.0f, 0.0f}
	};

	Vector3 scales[3] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
	};

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
		ImGui::SliderFloat3("translate[0]", &translates[0].x, -2, 2);
		ImGui::SliderFloat3("rotate[0]", &rotates[0].x, -2 * M_PI, 2 * M_PI);
		ImGui::SliderFloat3("scale[0]", &scales[0].x, 0, 5);
		ImGui::SliderFloat3("translate[1]", &translates[1].x, -2, 2);
		ImGui::SliderFloat3("rotate[1]", &rotates[1].x, -2 * M_PI, 2 * M_PI);
		ImGui::SliderFloat3("scale[1]", &scales[1].x, 0, 5);
		ImGui::SliderFloat3("translate[2]", &translates[2].x, -2, 2);
		ImGui::SliderFloat3("rotate[2]", &rotates[2].x, -2 * M_PI, 2 * M_PI);
		ImGui::SliderFloat3("scale[2]", &scales[2].x, 0, 5);
		ImGui::End();

		Matrix4x4 WorldS = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 WorldE = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		WorldE = Multiply(WorldE, WorldS);
		Matrix4x4 WorldH = MakeAffineMatrix(scales[2], rotates[2], translates[2]);
		WorldH = Multiply(WorldH, WorldE);

		Sphere Shoulder;
		Shoulder.center = { WorldS.m[3][0], WorldS.m[3][1], WorldS.m[3][2] };
		Shoulder.radius = 0.05f;
		Sphere Elbow;
		Elbow.center = { WorldE.m[3][0], WorldE.m[3][1], WorldE.m[3][2] };
		Elbow.radius = 0.05f;
		Sphere Hand;
		Hand.center = { WorldH.m[3][0], WorldH.m[3][1], WorldH.m[3][2] };
		Hand.radius = 0.05f;

		Segment line[2];
		line[0].origin = Shoulder.center;
		line[0].diff = Elbow.center - Shoulder.center;

		line[1].origin = Elbow.center;
		line[1].diff = Hand.center - Elbow.center;

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

		for (int i = 0; i < 2; i++) {
			DrawLine(line[i], viewProjectionMatrix, viewportMatrix, WHITE);
		}

		DrawSphere(Shoulder, viewProjectionMatrix, viewportMatrix, RED);

		DrawSphere(Elbow, viewProjectionMatrix, viewportMatrix, GREEN);
		
		DrawSphere(Hand, viewProjectionMatrix, viewportMatrix, BLUE);

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
