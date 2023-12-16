// @file: Projectile.cpp
//
// @brief: Projectile class, used to create projectiles
//
// @author: Alan
// @date: 2023/12
#include "GameCore.h"
#include "Projectile.h"

#define NDEBUG_ENEMY

IMPLEMENT_DYNAMIC_CLASS(Projectile)

void Projectile::Initialize()
{
	Component::Initialize();
	start_pos = ownerEntity->GetTransform().position;
	collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
	sprite= (Sprite*)ownerEntity->GetComponent("Sprite");
	
}

void Projectile::Update()
{
	
	Vec2 movementStep = dir * (speed * Time::Instance().DeltaTime());

	
	ownerEntity->GetTransform().position += movementStep;

	
	distanceTraveled += movementStep.Magnitude();
	for (const auto& other : collider->OnCollisionEnter())
	{
		if (other->GetOwner()->GetName() != "enemy")
		{
			continue;

		}
		ownerEntity->GetParentScene()->RemoveEntity(ownerEntity->GetUid());
	}

	// Check if the projectile has exceeded its range
	if (distanceTraveled > Range) {

		ownerEntity->GetParentScene()->RemoveEntity(ownerEntity->GetUid());
	
	}
}

void Projectile::SetSpeed(float spd)
{
	speed = spd;
}
void Projectile::SetDirection(Vec2 direction)
{
	dir = direction;
}
void Projectile::SetRange(float range)
{
	Range = range;
}