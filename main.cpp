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
#include "Spring.h"
#include "Ball.h"
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

	float deltaTime = 1.0f / 60.0f;
	const Vector3 kGravity{0.0f, -9.8f, 0.0f};

	Spring spring{};
	spring.anchor = { 0.0f, 1.0f, 0.0f };
	spring.naturalLength = 0.7f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	Ball ball{};
	ball.position = { 0.8f, 0.2f, 0.0f };
	ball.mass = 2.0f;
	ball.radiusu = 0.05f;
	ball.color = BLUE;

	bool isStart = false;

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
		if (!isStart) {
			isStart = ImGui::Button("isStart");
		}
		ImGui::End();

		if (isStart) {
			Vector3 diff = ball.position - spring.anchor;
			float length = Length(diff);

			if (length != 0.0f) {
				Vector3 direction = Normalize(diff);
				Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
				Vector3 displacement = length * (ball.position - restPosition);
				Vector3 restoringForce = -spring.stiffness * displacement;
				Vector3 dampingForce = -spring.dampingCoefficient * ball.velocity;
				Vector3 force = restoringForce + dampingForce + kGravity;
				ball.acceleration = (force / ball.mass);
			}
			ball.velocity += ball.acceleration / deltaTime;
			ball.position += ball.velocity / deltaTime;
		}

		Segment segment;
		segment.origin = spring.anchor;
		segment.diff = ball.position - spring.anchor;

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

		DrawLine(segment, viewProjectionMatrix, viewportMatrix, WHITE);

		DrawSphere({ball.position , ball.radiusu}, viewProjectionMatrix, viewportMatrix, ball.color);

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
