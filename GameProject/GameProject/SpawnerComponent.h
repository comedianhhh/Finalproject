// @file: SpawnerComponent.h
//
// @brief: SpawnerComponent is a component that spawns enemies
//
// @author: Alan
// @date: 2023/12
#pragma once
#ifndef _SPAWNERCOMPONENT_H_
#define _SPAWNERCOMPONENT_H_
#include "GameCore.h"
#include "HealhComponent.h"
class SpawnerComponent: public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(SpawnerComponent, Component)
private:
	float spawnInterval;
	float lastSpawnTime;
	int spawnCount;
	std::function<void()> spawnFunction;
	enum class SpawnerType {
		One,
		Two,
		Three
	};
	SpawnerType spawnType;
	HealhComponent* health;
	BoxCollider* collider;

public:


	void Initialize() override;
	void Update() override;
	void Load(json::JSON&) override;
	void SetSpawnInterval(float interval);
	void SetSpawnFunction(SpawnerType);

	void OnDeath();




};

#endif // !_SPAWNERCOMPONENT_H_