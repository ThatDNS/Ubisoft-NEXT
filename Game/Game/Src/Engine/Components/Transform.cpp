// @file: Transform.cpp
//
// @brief: Cpp file for Transform class.

#include "stdafx.h"

#include "Engine/Components/Transform.h"
#include "Engine/Math/Vector2.h"

IMPLEMENT_DYNAMIC_CLASS(Transform)

Transform::Transform() :
	position(Vector2(0, 0)), rotation(0), scale(Vector2(1, 1))
{}

void Transform::Load(json::JSON& transformJSON)
{
	if (transformJSON.hasKey("Position")) {
		position.x = (float)transformJSON["Position"][0].ToFloat();
		position.y = (float)transformJSON["Position"][1].ToFloat();
	}
	if (transformJSON.hasKey("Rotation"))
	{
		rotation = (float)transformJSON["Rotation"].ToFloat();
	}
	if (transformJSON.hasKey("Scale"))
	{
		scale.x = (float)transformJSON["Scale"][0].ToFloat();
		scale.y = (float)transformJSON["Scale"][1].ToFloat();
	}
}

void Transform::Destroy() {}

void Transform::Translate(const Vector2& delta) {
	position += delta;
}

void Transform::Rotate(float delta) {
	rotation += delta;
}

void Transform::Scale(const Vector2& delta) {
	scale += delta;
}

