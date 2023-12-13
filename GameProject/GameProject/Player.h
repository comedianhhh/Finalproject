#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameCore.h"

class Player : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(Player, Component)

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
    STRCODE game_over_scene = -1;

private:
    void Fire();
    float cooldown = 0.5f;
    float last_fire = 0.0f;
};

#endif // PLAYER_H


