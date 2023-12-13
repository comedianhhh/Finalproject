#pragma once
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "GameCore.h"
#include "Sprite.h"

class Projectile: public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Projectile,Component)
public:
	enum class ProjectileType {
		Player,
		Enemy
	};
	void Initialize() override;
	void Update() override;
	void SetDirection(Vec2 direction);
	void SetSpeed(float spd);
	void SetRange(float range);
public:
	Vec2 dir;

private:
	float speed;// Speed
	float damage;// Damage
	float Range;// Range
	Vec2 start_pos;
	Sprite* sprite = nullptr;
	BoxCollider* collider = nullptr;
	ProjectileType type; // Type of projectile
	float distanceTraveled = 0.0f;
};

#endif // _PROJECTILE_H_




