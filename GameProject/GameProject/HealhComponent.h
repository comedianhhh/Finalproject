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

public:
	void SetHealth(float hp);
	float GetHealth() const;
	void SetMaxHealth(float hp);
	float GetMaxHealth() const;
	void TakeDamage(float dmg);
	void Heal(float hp);
	void ResetHealth();
};


#endif // !_HEALHCOMPONENT_H_