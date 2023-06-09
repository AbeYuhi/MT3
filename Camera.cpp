#include "Camera.h"


Camera::Camera()
{
}

Camera::~Camera()
{
}


void Camera::Initialize() {

	scale_ = { 1, 1, 1 };
	translate_ = { 0.0f, 1.9f, -6.49f };
	rotate_ = { 0.26f, 0.0f, 0.0f };
	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, translate_);

	//マウスの位置
	mousePos_ = {0, 0};
	preMousePos_ = {0, 0};
}

void Camera::Update(char keys[]) {

	ImGui::Begin("CameraManager");
	ImGui::SliderFloat3("CameraTranslate", &translate_.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("CameraRotate", &rotate_.x, -2.0f * M_PI, 2.0f * M_PI);
	ImGui::End();

	preMousePos_ = mousePos_;
	Novice::GetMousePosition(&mousePos_.x, &mousePos_.y);

	if (Novice::IsPressMouse(1)) {
		Vector2Int mouseAmount = mousePos_ - preMousePos_;

		rotate_.x += mouseAmount.y * 0.02f;
		rotate_.y += mouseAmount.x * 0.02f;
	}

	if (Novice::IsPressMouse(2)) {
		Vector2Int mouseAmount = mousePos_ - preMousePos_;

		translate_.x += -mouseAmount.x * 0.1f;
		translate_.y += mouseAmount.y * 0.1f;
	}

	Vector3 cameraVelocity = { 0.0f, 0.0f, 0.0f };
	if (keys[DIK_A]) {
		cameraVelocity.x = -0.2f;
	}
	if (keys[DIK_D]) {
		cameraVelocity.x = 0.2f;
	}
	if (keys[DIK_W]) {
		cameraVelocity.z = 0.2f;
	}
	if (keys[DIK_S]) {
		cameraVelocity.z = -0.2f;
	}

	int wheel = Novice::GetWheel();
	if (wheel != 0) {
		cameraVelocity.z += wheel * 0.01f;
	}

	translate_ += TransformNormal(cameraVelocity, worldMatrix_);

	worldMatrix_ = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate_, translate_);
}