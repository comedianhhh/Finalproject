#include "GameCore.h"
#include "SpawnerComponent.h"
#include "Time.h"
#include "TextureAsset.h"
#include "AnimatedSprite.h"
#include "Enemy.h"

IMPLEMENT_DYNAMIC_CLASS(SpawnerComponent)

SpawnerComponent::SpawnerComponent()
	: lastSpawnTime(0), spawnInterval(10.0f), spawnType(SpawnerType::One) {
	std::cout<<"SpawnerComponent created"<<std::endl;
	SetSpawnFunction(spawnType);

}
void SpawnerComponent::Initialize()
{
	// Initialize lastSpawnTime to the current time to start counting from now.
	Component::Initialize();
	lastSpawnTime = Time::Instance().TotalTime();

	
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
			std::cout<< "Enemy spawned" << std::endl;
			// List the components that the enemy entity requires.
			std::vector<std::string> components = { "BoxCollider"};

			// Add the necessary components to the enemy entity.
			enemy->AddComponents(components);
			Enemy* enemyComponent = (Enemy*)enemy->CreateComponent("Enemy");

			enemyComponent->setAttributes(100);
			
			// Load the texture asset for the enemy.
			TextureAsset* enemyTexture = (TextureAsset*)AssetManager::Get().GetAsset("bat");
			// Obtain the sprite component and set the enemy texture.
			AnimatedSprite* enemySprite = (AnimatedSprite*)enemy->CreateComponent("AnimatedSprite");
			BoxCollider* enemyCollider = (BoxCollider*)enemy->CreateComponent("BoxCollider");

			enemySprite->SetTextureAsset(enemyTexture);
			enemySprite->SetSpriteSheet(1, 6, 6);
			


			// Set the enemy's initial position. You can customize this position.
			enemy->GetTransform().position = ownerEntity->GetTransform().position;
			enemy->GetTransform().scale=Vec2(0.8f,0.8f);
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