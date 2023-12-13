#include "GameCore.h"
#include "Enemy.h"
#include "Player.h"

#define NDEBUG_ENEMY

IMPLEMENT_DYNAMIC_CLASS(Enemy)


void Enemy::Initialize()
{
	Component::Initialize();
	start_pos = ownerEntity->GetTransform().position;
	collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
	healthcomponent = (HealhComponent*)ownerEntity->GetComponent("HealhComponent");
}

//Enemy should move towards the player
void Enemy::Update() 
{
#pragma region Move
	Chase();
#pragma endregion
	if (collider == nullptr) 
	{
		return;
	}
	
	for (const auto& other : collider->OnCollisionEnter())
	{
		if (other->GetOwner()->GetName() != "PlayerBullet")
		{
			continue;
			
		}
		std::cout << "hit" << std::endl;
		healthcomponent->TakeDamage(1.0);
	}
}

Vec2 Enemy::GetPosition()
{
	return ownerEntity->GetTransform().position;
}

Vec2 Enemy::GetPlayerPosition()
{

	const Scene* parentScene = ownerEntity->GetParentScene();
	if (!parentScene) {
		// Handle the case where there's no parent scene
		return Vec2::Zero;
	}

	std::list<Entity*> playerEntities = ownerEntity->GetParentScene()->FindEntityWithComponent("Player");

	if (playerEntities.empty()) {
		// Handle the case where there are no player entities
		return Vec2::Zero;
	}
	// Initialize variables to track the closest player entity and its position
	Entity* closestPlayer = nullptr;
	float closestDistance = std::numeric_limits<float>::max();

	// Loop through the player entities to find the closest one
	for (Entity* player : playerEntities) {
		Vec2 playerPos = player->GetTransform().position;
		float distance = (playerPos - GetPosition()).MagnitudeSquared();

		if (distance < closestDistance) {
			closestPlayer = player;
			closestDistance = distance;
		}
	}

	if (closestPlayer) {
		// Return the position of the closest player
		return closestPlayer->GetTransform().position;
	}
	else {
		// Handle the case where no player entity is found
		return Vec2::Zero;
	}
}


void Enemy::Load(json::JSON& node)
{
	Component::Load(node);
	if (node.hasKey("Speed"))
	{
		speed = static_cast<float>(node.at("Speed").ToFloat());
	}
}
void Enemy::setAttributes(float spd)
{
	speed = spd;
}void Enemy::Chase() 
{
	// Get the position of the player and the enemy
	Vec2 playerPos = GetPlayerPosition(); // Implement a function to get player position
	Vec2 enemyPos = GetPosition(); // Implement a function to get enemy position

	// Calculate the direction from the enemy to the player
	Vec2 dir = playerPos - enemyPos;

	// Normalize the direction vector if it's not zero
	if (dir != Vec2::Zero) {
		dir.Normalize();
	}


	// Move the enemy in the calculated direction
	ownerEntity->GetTransform().position += dir * (speed * Time::Instance().DeltaTime());

	// Rest of your code here for handling input or other behaviors
}
