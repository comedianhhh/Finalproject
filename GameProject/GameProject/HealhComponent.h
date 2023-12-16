// @file: HealhComponent.h
//
// @brief: HealhComponent class declaration
//
// @author: Alan
// @date: 2023/12
#pragma once
#ifndef _HEALHCOMPONENT_H_
#define _HEALHCOMPONENT_H_
#include "GameCore.h"

class HealhComponent : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(HealhComponent, Component)

public:
	void Initialize() override;
	void Update() override;
	void Load(json::JSON&) override;
private:
	float currenthealth = 5;
	float maxhealth = 5;
	bool isDead = false;
	Vec2 originalScale;
	SDL_Color hit_effect_color = { 255,0,0,100 };
	SDL_Color health_color= { 255, 255, 255 ,255};

public:
	bool CheckDead (){ return isDead; }
	void SetHealth(float hp);
	float GetHealth() const;
	void SetMaxHealth(float hp);
	float GetMaxHealth() const;
	void TakeDamage(float dmg);
	void Heal(float hp);
	void ResetHealth();
	void TriggerHitEffect();
	void OnDeath();
	void AddHealth(float hp){ currenthealth += hp; }
};


#endif // !_HEALHCOMPONENT_H_