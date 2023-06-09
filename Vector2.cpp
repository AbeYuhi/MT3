#include "Vector2.h"

Vector2Int operator+(Vector2Int num1, Vector2Int num2) {
	return { num1.x + num2.x, num1.y + num2.y };
}

Vector2Int operator-(Vector2Int num1, Vector2Int num2) {
	 return { num1.x - num2.x, num1.y - num2.y };
}

Vector2Int UVConversion(const Vector2Int& textureSize, float u, float v) {
	Vector2Int pos;

	pos.x = int(textureSize.x * u);
	pos.y = int(textureSize.y * v);

	return pos;
}