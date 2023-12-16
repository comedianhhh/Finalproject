// @file: Enemy.h
//
// @brief: Enemy class declaration
//
// @author: Alan
// @date: 2023/12
#pragma once

#ifndef Enemy_H
#define Enemy_H

#include "GameCore.h"

class Enemy : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Enemy, Component)

public:

	void Initialize() override;
	void Update() override;
	void Load(json::JSON&) override;
	void setAttributes(float spd);
private:
	float speed = 5.0f;
	int attack = 1;
	HUD* hud;
	Vec2 start_pos;
	BoxCollider* collider = nullptr;
	HealhComponent* healthcomponent = nullptr;

private:
	Vec2 GetPlayerPosition();
	Vec2 GetPosition();
	void Chase();
	void OnDeath();
};

#endif // Enemy_H