// @file: LevelGenerator.cpp
//
// @brief: Cpp file for LevelGenerator class responsible for generating level as per the position of player.

#include "stdafx.h"
#include "Game/LevelGenerator.h"
#include "Engine/Systems/SceneManager.h"
#include "Engine/Systems/Scene.h"
#include "Engine/Core/Logger.h"
#include "Engine/Components/Entity.h"
#include "Engine/Components/Component.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/MeshRenderer.h"
#include "Engine/Math/Vector3.h"

void LevelGenerator::Initialize()
{
	// Find the player entity and cache it
	std::list<Entity*> matchedEntities = SceneManager::Get().GetActiveScene()->FindEntityWithComponent(BallSpawnerC);
	if (matchedEntities.size() == 0)
	{
		Logger::Get().Log("Could not find ball spawner");
	}
	else
	{
		playerEntity = matchedEntities.front();
	}
}

void LevelGenerator::Update(float deltaTime)
{
	float playerPosition = playerEntity->GetTransform().position.z;
	float canSeeTill = playerPosition + maxSightDistance;
	while (lastSpawnDistance + SEPARATION_DIST <= canSeeTill)
	{
		// Spawn level
		lastSpawnDistance += SEPARATION_DIST;
		SpawnLevel(lastSpawnDistance);
	}
}

void LevelGenerator::CreateWallEntity(Vector3& position, Vector3& scale)
{
	Entity* entity = SceneManager::Get().GetActiveScene()->CreateEntity(std::vector<ComponentType>{ MeshRendererC, BoxColliderC });
	entity->SetName("Wall");

	// Load the transform data
	entity->GetTransform().position = position;
	entity->GetTransform().scale = scale;

	// Load wall mesh
	Component* component = entity->GetComponent(MeshRendererC);
	MeshRenderer* mr = static_cast<MeshRenderer*>(component);
	mr->LoadMesh("Assets/Objects/cube.obj");
	mr->SetRenderBackSide(false);
	mr->SetMeshColor(Vector3(0.8f, 0.8f, 0.8f));
	
	// Initialize
	entity->Initialize();
}

void LevelGenerator::CreateBreakableEntity(Vector3& position, Vector3& scale)
{
	Entity* entity = SceneManager::Get().GetActiveScene()->CreateEntity(std::vector<ComponentType>{ MeshRendererC, BoxColliderC, RigidBodyC, ParticlesC, BreakableC });
	entity->SetName("Breakable");
	entity->GetTransform().position = position;
	entity->GetTransform().scale = scale;

	// Initialize
	entity->Initialize();
}

void LevelGenerator::SpawnLevel(float zPos)
{
	Vector3 wallScale{ 6.0f, 8.0f, 5.0f };
	Vector3 breakableScale{ 2.0f, 2.0f, 2.0f };

	CreateWallEntity     (Vector3(-15.0f, -12.0f, zPos), wallScale);
	CreateBreakableEntity(Vector3(-15.0f, 0.0f, zPos),   breakableScale);
	CreateWallEntity     (Vector3(0.0f, -12.0f, zPos),   wallScale);
	CreateBreakableEntity(Vector3(0.0f, 0.0f, zPos),     breakableScale);
	CreateWallEntity     (Vector3(15.0f, -12.0f, zPos),  wallScale);
	CreateBreakableEntity(Vector3(15.0f, 0.0f, zPos),    breakableScale);
}

