// @file: HUD.h
//
// @brief: HUD class, used to display the time, the player's health and kill count
//
// @author: Alan
// @date: 2023/12
#pragma once
#ifndef _HUD_H_
#define _HUD_H_
#include "GameCore.h"
#include"Component.h""
#include"FontAsset.h"
#include"FontSprite.h"
#include"Sprite.h"
class HUD: public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(HUD,Component)
private:
	void Initialize() override;
	void Update() override;
	void Load(json::JSON&) override;
	void SetInvisible();

private:
	int KillCount;
	float time;
	bool isvisible;
	std::vector<Sprite*> heartSprites;
	int playerHealth;
	int maxHealth;


public :
	void setKillCount(int count);
	// Returns the current kill count
	int getKillCount() const;

	// Sets the game time and updates the HUD display
	void setTime(float time);
	// Returns the current game time
	float getTime() const;
	void SetPlayerHealth(int health);
	void ShowKillCount(Vec2 transform);
	void ShowHealth(Vec2 transform);

	

private:
	FontAsset* fontasset=nullptr;
	FontSprite* font=nullptr;
	Vec2 originalscalesize;

	float alpha;
	float timer= 0.0f;
	float lastKillTime =0.0f;
	const float visibilityThreshold = 4.0f;



};

#endif	_HUD_H_
