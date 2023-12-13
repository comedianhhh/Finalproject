#include "GameCore.h"
#include "SpawnerComponent.h"
#include "Time.h"
#include "TextureAsset.h"
#include "AnimatedSprite.h"
#include "Enemy.h"

IMPLEMENT_DYNAMIC_CLASS(SpawnerComponent)

void SpawnerComponent::Initialize()
{

	Component::Initialize();
	lastSpawnTime = Time::Instance().TotalTime();
	lastSpawnTime = 0;
	spawnInterval = 10.0f;
	SetSpawnFunction(spawnType);
	
}
void SpawnerComponent::Update()
{
	
	if (Time::Instance().TotalTime() - lastSpawnTime > spawnInterval) {
		spawnFunction();
		lastSpawnTime = Time::Instance().TotalTime();
	}
}

void SpawnerComponent::Load(json::JSON& node)
{
	Component::Load(node);

	if (node.hasKey("spawnInterval")) {
		spawnInterval = static_cast<float>(node.at("spawnInterval").ToFloat());
	}
	if (node.hasKey("spawnCount")) {
		spawnCount = static_cast<float>(node.at("spawnCount").ToInt());
	}
	if (node.hasKey("spawnType")) {
		std::string type = node.at("spawnType").ToString();
		if (type == "One") {
			spawnType = SpawnerType::One;
		}
		else if (type == "Two") {
			spawnType = SpawnerType::Two;
		}
		else if (type == "Three") {
			spawnType = SpawnerType::Three;
		}
		else {
			spawnType = SpawnerType::One;
		}
	}


}
void SpawnerComponent::SetSpawnInterval(float interval)
{
	spawnInterval = interval;
}
void SpawnerComponent::SetSpawnFunction(SpawnerType type) {
	switch (type) {
	case SpawnerType::One:
		spawnFunction = [this]() {
			// Enemy spawn logic goes here
			Entity* enemy = ownerEntity->GetParentScene()->CreateEntity();
			enemy->SetName("enemy");
			// Set the enemy's initial position. You can customize this position.
			enemy->GetTransform().position = ownerEntity->GetTransform().position;
			enemy->GetTransform().scale = Vec2(1.0f, 1.0f);
	

			TextureAsset* enemyTexture = (TextureAsset*)AssetManager::Get().GetAsset("bat");
			// Obtain the sprite component and set the enemy texture.
			AnimatedSprite* enemySprite = (AnimatedSprite*)enemy->CreateComponent("AnimatedSprite");

			enemySprite->SetTextureAsset(enemyTexture);
			enemySprite->SetSpriteSheet(1, 6, 6);
			
			std::vector<std::string> components = { "BoxCollider" };
			enemy->AddComponents(components);

			HealhComponent* healthcomponent = (HealhComponent*)enemy->CreateComponent("HealhComponent");
			healthcomponent->SetHealth(3.0);

			
			// Load the texture asset for the enemy.

			Enemy* enemyComponent = (Enemy*)enemy->CreateComponent("Enemy");

			enemyComponent->setAttributes(100);

			};
		break;
	case SpawnerType::Two:
		spawnFunction = [this]() {
			// PowerUp spawn logic goes here
			Entity* powerUp = ownerEntity->GetParentScene()->CreateEntity();
			std::cout << "Enemy two spawned" << std::endl;
			// ... rest of power-up spawning code ...
			};
		break;
	
	case SpawnerType::Three:
		spawnFunction = [this]() {
			// PowerUp spawn logic goes here
			Entity* powerUp = ownerEntity->GetParentScene()->CreateEntity();
			std::cout << "Enemy three spawned" << std::endl;
			};
		break;
	default:
		// It's a good idea to set a default no-op or error-logging function
		spawnFunction = [this]() {
			Entity* enemy = ownerEntity->GetParentScene()->CreateEntity();
			std::cout<< "Invalid spawn type" << std::endl;
			};
		break;
	}
}