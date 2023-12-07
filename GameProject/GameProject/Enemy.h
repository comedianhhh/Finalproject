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
private:
	float speed = 5.0f;
	int health = 3;
	int attack = 1;
	Vec2 start_pos;
	BoxCollider* collider = nullptr;

private:
	Vec2 GetPlayerPosition();
	Vec2 GetPosition();
};

#endif // Enemy_H