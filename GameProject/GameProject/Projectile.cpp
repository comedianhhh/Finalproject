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

	collider->SetSize(10, 10);
	
}

void Projectile::Update()
{
	ownerEntity->GetTransform().position+=dir*(speed*Time::Instance().DeltaTime());
}

void Projectile::SetSpeed(float spd)
{
	speed = spd;
}
void Projectile::SetDirection(Vec2 direction)
{
	dir = direction;
}