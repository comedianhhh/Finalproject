// @file: Loot.h
//
// @brief: Loot class, used to create loot objects in the game
//
// @author: Alan
// @date: 2023/12
#pragma once
#ifndef _LOOT_H_
#define _LOOT_H_
#include "GameCore.h"

class Loot: public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Loot,Component)
	enum class LootType
	{
		HEALTH,
		WEAPON,
		AMMO
	};
public:
	void Initialize() override;
	void Update() override;
	void Load(json::JSON&) override;

	void SetLootType(LootType type){ loottype = type; }
private:
	BoxCollider* boxCollider;
	LootType loottype;

};



#endif
