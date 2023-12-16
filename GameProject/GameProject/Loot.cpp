// @file: Loot.cpp
//
// @brief: Loot class, used to create loot in the game
//
// @author: Alan
// @date: 2023/12
#include "GameCore.h"
#include "Loot.h"

IMPLEMENT_DYNAMIC_CLASS(Loot)

void Loot::Initialize()
{
	loottype = LootType::HEALTH;
	boxCollider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");

}
void Loot::Update()
{
	if(boxCollider==nullptr)  {
		return;
	}
	for (const auto& other : boxCollider->OnCollisionEnter())
	{
		if (other->GetOwner()->GetName() != "Player")
		{
			continue;
		}
		if (loottype == LootType::HEALTH)
		{
			HealhComponent* hl = (HealhComponent*)other->GetOwner()->GetComponent("HealhComponent");
			hl->AddHealth(1);
			LOG("Health+1");
			ownerEntity->GetParentScene()->RemoveEntity(ownerEntity->GetUid());
		}
		else if (loottype == LootType::WEAPON)
		{
			LOG("Weapon");
		}

	}
	
}
void Loot::Load(json::JSON& node)
{
	if(node.hasKey("LootType"))
	{
		std::string type = node["LootType"].ToString();
		if (type=="HEALTH")
		{
			loottype=LootType::HEALTH;
		}
		else if (type=="WEAPON")
		{
			loottype = LootType::WEAPON;
		}

	}
}