#include <Novice.h>
#include <ImGuiManager.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector3_Math.hpp"
#include "Matrix4x4.h"
#include "Grid.h"
#include "Sphere.h"
#include "Camera.h"
#define M_PI 3.14f

const char kWindowTitle[] = "LE2A_02_アベユウヒ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = { 0 };

	uint32_t sphereTexture = Novice::LoadTexture("./Resources/Images/uvChecker.png");

	Sphere s1;
	unsigned int s1Color = WHITE;
	s1.center = { 0.0f, 0.0f, -1.0f};
	s1.radius = 1.0f;

	Sphere s2;

	s2.center = { 0.0f, 0.0f, 1.0f };
	s2.radius = 1.0f;
	unsigned int s2Color = WHITE;

	Camera* camera = new Camera();
	camera->Initialize();

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
		
		ImGui::Begin("Sphere");
		ImGui::SliderFloat3("s1Pos", &s1.center.x, -10, 10);
		ImGui::SliderFloat("s1Radius", &s1.radius, 0, 10);
		ImGui::SliderFloat3("s2Pos", &s2.center.x, -10, 10);
		ImGui::SliderFloat("s2Radius", &s2.radius, 0, 10);
		ImGui::End();

		if (IsCollision(s1, s2)) {
			s1Color = RED;
		}
		else {
			s1Color = WHITE;
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

		DrawSphere(s1, viewProjectionMatrix, viewportMatrix, s1Color);
		DrawSphere(s2, viewProjectionMatrix, viewportMatrix, s2Color);


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

	//解放処理
	delete camera;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
