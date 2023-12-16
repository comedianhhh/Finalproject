// @file: Player.h
//
// @brief: Player class, which is a Component, is the main character of the game.
//
// @author: Alan
// @date: 2023/12
#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameCore.h"
#include "BoxCollider.h"
#include "HealhComponent.h"
#include "HUD.h"
class Player : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(Player, Component)

public:
    void Initialize() override;
    void Update() override;
    void Load(json::JSON&) override;
private:
    float speed = 5.0f;
    int attack = 1;
    Vec2 start_pos;
    BoxCollider* collider = nullptr;
    HealhComponent* health = nullptr;
    HUD* hud = nullptr;
    STRCODE game_over_scene = -1;

private:
    void Fire();
    float cooldown = 0.5f;
    float last_fire = 0.0f;
    int lasthealth = 0;
};

#endif // PLAYER_H


