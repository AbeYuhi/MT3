#pragma once
#include <Novice.h>
#include <ImGuiManager.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector3_Math.hpp"
#include "Matrix4x4.h"
#define M_PI 3.14f

class Camera
{
public:
	Camera();
	~Camera();

	void Initialize();

	void Update(char keys[]);

	inline Vector3 GetRotate() { return rotate_; }
	inline Vector3 GetTranslate() { return translate_; }
	inline Matrix4x4 GetWorldTransform() { return worldMatrix_; }

private:
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 translate_;

	Matrix4x4 worldMatrix_;

	//マウスの位置
	Vector2Int mousePos_;
	Vector2Int preMousePos_;
};
