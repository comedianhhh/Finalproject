#include "GameCore.h"
#include "HealhComponent.h"
#include "Time.h"
#include "AnimatedSprite.h"



IMPLEMENT_DYNAMIC_CLASS(HealhComponent)

void HealhComponent::Initialize()
{
	Component::Initialize();
	currenthealth = maxhealth;
}

void HealhComponent::Update()
{
	if (currenthealth <= 0)
	{
		std::cout<<ownerEntity->GetName()<<" is dead"<<std::endl;
		ownerEntity->GetParentScene()->RemoveEntity(ownerEntity->GetUid());
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
void HealhComponent::TakeDamage(float dmg)
{
	currenthealth -= dmg;
	TriggerHitEffect();


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

	// Save the original scale
	Vec2 originalScale = transform.scale;

	// Increase the scale to create a "pulse" effect
	Vec2 largerScale = originalScale * 1.2f; // Scale up by 20%
	transform.Scale(largerScale);

	// Schedule a task to reset the scale after a short delay
	Time::Instance().ScheduleTask(0.2f, [&transform, originalScale]() {
		transform.scale = originalScale;
		LOG("change scale")
		});

	// Apply a knockback effect
	Vec2 knockbackDirection = Vec2(0.0f, -1.0f); // Assuming a negative Y value for "upward"
	float knockbackForce = 6.0f; // Adjust as necessary
	transform.position += knockbackDirection * knockbackForce;

}