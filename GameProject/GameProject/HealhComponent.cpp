// @file: HealhComponent.cpp
//
// @brief: Health component for the player and enemies
//
// @author: Alan
// @date: 2023/12
#include "GameCore.h"
#include "HealhComponent.h"
#include "Time.h"
#include "AnimatedSprite.h"



IMPLEMENT_DYNAMIC_CLASS(HealhComponent)

void HealhComponent::Initialize()
{
	Component::Initialize();
	currenthealth = maxhealth;
	originalScale = ownerEntity->GetTransform().scale;
}

void HealhComponent::Update()
{
	if (currenthealth <= 0)
	{
		isDead = true;
	}

}
void HealhComponent::Load(json::JSON& node)
{
	Component::Load(node);
	if (node.hasKey("MaxHealth"))
	{
		maxhealth = node["MaxHealth"].ToFloat();
	}

}

void HealhComponent::SetHealth(float hp)
{
	currenthealth = hp;
}
void HealhComponent::SetMaxHealth(float hp)
{
	maxhealth = hp;
}
float HealhComponent::GetHealth() const
{
	return currenthealth;
}
float HealhComponent::GetMaxHealth() const
{
	return maxhealth;
}

void HealhComponent::OnDeath()
{

}
void HealhComponent::TakeDamage(float dmg)
{
	currenthealth -= dmg;
	TriggerHitEffect();
	LOG(ownerEntity->GetGuid()<<"  Hurt!")

}
void HealhComponent::Heal(float hp)
{
	currenthealth += hp;
}
void HealhComponent::ResetHealth()
{
	currenthealth = maxhealth;
}
void HealhComponent::TriggerHitEffect()
{

	// Obtain the sprite component from the owner entity
	AnimatedSprite* sprite = (AnimatedSprite*)ownerEntity->GetComponent("AnimatedSprite");
	if (sprite)
	{
		
		// Change the color of the sprite to red
		sprite->SetFilterColor(hit_effect_color);

		// Schedule a task to reset the color after a short delay

		SDL_Color originalColor = health_color; 
		Time::Instance().ScheduleTask(0.5f, [sprite, originalColor]() 
			{ 
			sprite->SetFilterColor(originalColor); 
			});
	}

	// If you have a transform component and want to apply a knockback effect
	Transform& transform = ownerEntity->GetTransform();

	// Increase the scale to create a "pulse" effect
	Vec2 largerScale = originalScale * 1.2f; // Scale up by 20%
	transform.Scale(largerScale);
	Vec2 temp = originalScale;
	// Schedule a task to reset the scale after a short delay
	Time::Instance().ScheduleTask(0.2f, [&transform, temp]() {
		transform.scale = temp;
		});

	// Apply a knockback effect
	Vec2 knockbackDirection = Vec2(0.0f, -1.0f); // Assuming a negative Y value for "upward"
	float knockbackForce = 6.0f; // Adjust as necessary
	transform.position += knockbackDirection * knockbackForce;

}