#include "GameCore.h"
#include "HealhComponent.h"


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
}
void HealhComponent::Heal(float hp)
{
	currenthealth += hp;
}
void HealhComponent::ResetHealth()
{
	currenthealth = maxhealth;
}
