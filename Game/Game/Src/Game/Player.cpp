// @file: Player.cpp
//
// @brief: Cpp file for player functionalities.

#include "stdafx.h"

#include "Game/Player.h"
#include "App/app.h"
#include "Engine/Core/Logger.h"
#include "Engine/Components/Sprite.h"
#include "Engine/Components/Entity.h"
#include "Engine/Components/Component.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/BoxCollider.h"
#include "Engine/Components/RigidBody.h"
#include "Engine/Math/Vector3.h"
#include "Engine/Systems/RenderSystem.h"
#include "Engine/Systems/CollisionSystem.h"

void Player::Initialize()
{
	// Cache components
	collider = static_cast<BoxCollider*>(GetEntity()->GetComponent(BoxColliderC));
	rigidBody = static_cast<RigidBody*>(GetEntity()->GetComponent(RigidBodyC));

	// Attach camera to the player
	RenderSystem::Get().AttachCamera(GetEntity());
}

void Player::Update(float deltaTime)
{
	Move(deltaTime);
	Rotate(deltaTime);
}

void Player::Move(float deltaTime)
{
	Vector3 moveVector{ 0.0f, 0.0f, 0.0f };
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		++moveVector.x;
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		--moveVector.x;
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		++moveVector.y;
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		--moveVector.y;
	}

	moveVector.Normalize();
	moveVector = moveVector * (moveSpeed * deltaTime / 100.0f);

	// Move the entity
	rigidBody->ApplyForce(moveVector);
}

void Player::Rotate(float deltaTime)
{
	Vector3 rotateDir{ -App::GetController().GetRightThumbStickX(), App::GetController().GetRightThumbStickY(), 0.0f };
	rotateDir.Normalize();
	if (rotateDir.Magnitude() == 0)
		return;

	// Rotate the entity
	GetEntity()->CartesianRotationZ(rotateDir, collider, rotateSpeed * deltaTime / 100.0f);
}
