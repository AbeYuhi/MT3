#pragma once
#include "Vector3.h"

struct Ball {
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float mass;
	float radiusu;
	unsigned int color;
};