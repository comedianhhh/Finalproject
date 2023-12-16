// @file: Player.cpp
//
// @brief: Player class, used to control the player's movement and fire
//
// @author: Alan
// @date: 2023/12
#include "GameCore.h"
#include "Player.h"
#include "Sprite.h"
#include "BoxCollider.h"
#include "Projectile.h"

#include "AssetManager.h"
#define NDEBUG_PLAYER

IMPLEMENT_DYNAMIC_CLASS(Player)

void Player::Initialize()
{
    Component::Initialize();
    start_pos = ownerEntity->GetTransform().position;
    collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
    health = (HealhComponent*)ownerEntity->GetComponent("HealhComponent");
    lasthealth = health->GetHealth();
    auto hudlist= ownerEntity->GetParentScene()->FindEntityWithComponent("HUD");
    if (hudlist.size() > 0)
	{
		hud = (HUD*)hudlist.front()->GetComponent("HUD");
	}
	else
	{
		LOG("no hud found");
	}
}
void Player::Update() 
{
    if(health->GetHealth()!=lasthealth)
	{
		lasthealth = health->GetHealth();
        hud->SetPlayerHealth(lasthealth);
        hud->ShowHealth(ownerEntity->GetTransform().position);
	}

    if (health->CheckDead())
    {

        std::cout << ownerEntity->GetName() << " is dead" << std::endl;
  
		Scene* current_scene = SceneManager::Get().GetActiveScene();
		if (SceneManager::Get().SetActiveScene(game_over_scene))
		{
			current_scene->isEnabled = false;
		}
    }

#pragma region Input


    Vec2 dir = Vec2::Zero;
    const InputSystem& input = InputSystem::Instance();

    // Handle horizontal movement
    if (input.isKeyPressed(SDLK_LEFT) || input.isKeyPressed(SDLK_a) || input.isGamepadButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
        dir.x -= 1;
    }
    if (input.isKeyPressed(SDLK_RIGHT) || input.isKeyPressed(SDLK_d) || input.isGamepadButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
        dir.x += 1;
    }

    // Handle vertical movement
    if (input.isKeyPressed(SDLK_UP) || input.isKeyPressed(SDLK_w) || input.isGamepadButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
        dir.y -= 1;
    }
    if (input.isKeyPressed(SDLK_DOWN) || input.isKeyPressed(SDLK_s) || input.isGamepadButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
        dir.y += 1;
    }
    //fire

    if(input.isMouseButtonPressed(SDL_MOUSEBUTTONDOWN)&& Time::Instance().TotalTime()-last_fire>cooldown)
	{
		Fire();
        last_fire = Time::Instance().TotalTime();
        std::cout<<"fire"<< std::endl;
	}
    // Handle gamepad analog stick input
    if (dir == Vec2::Zero) {
        dir.x = input.getGamepadAxisState(0, SDL_CONTROLLER_AXIS_LEFTX);
        dir.y = input.getGamepadAxisState(0, SDL_CONTROLLER_AXIS_LEFTY);
    }

    // Normalize the direction vector if it's not zero
    if (dir != Vec2::Zero) {
        dir.Normalize();
#pragma endregion
#ifdef DEBUG_PLAYER
        LOG("Input: " << dir.x << ", " << dir.y);
#endif
    }

    // Move the player
    ownerEntity->GetTransform().position += dir * (speed * Time::Instance().DeltaTime());

    if (collider == nullptr)
    {
        LOG("no collider uwu");
        return;
    }
    for (const auto& other: collider->OnCollisionEnter())
    {
	    if (other->GetOwner()->GetName() != "Enemy")
	    {
            continue;
        }



        ownerEntity->GetTransform().position = start_pos;
    }
}
void Player::Load(json::JSON& node)
{
    Component::Load(node);
    if (node.hasKey("Speed"))
    {
        speed = static_cast<float>(node.at("Speed").ToFloat());
    }

    if (node.hasKey("DeathScene"))
    {
	    game_over_scene = GetHashCode(node.at("DeathScene").ToString().c_str());
    }
}
void Player::Fire()
{
    Entity* bullet=ownerEntity->GetParentScene()->CreateEntity();
    bullet->SetName("PlayerBullet");
    TextureAsset* bulletTexture = (TextureAsset*)AssetManager::Get().GetAsset("ddcf9a11-4797-4a5b-940b-25ccf471bf62");
    Sprite* bulletSprite = (Sprite*)bullet->CreateComponent("Sprite");
    bulletSprite->SetTextureAsset(bulletTexture);

	std::vector<std::string> components = { "BoxCollider" };
	bullet->AddComponents(components);
    bullet->GetTransform().position = ownerEntity->GetTransform().position;
    bullet->GetTransform().Scale(Vec2(1.3,1.3));



	Vec2 targetPos;
	// Get mouse position and adjust by camera position.
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	targetPos = Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	// Calculate direction and set velocity.
	Vec2 direction = targetPos - ownerEntity->GetTransform().position;
    direction.Normalize();

	// Assuming bullet has a ProjectileComponent to set its velocity.
	Projectile* projectile = (Projectile*)bullet->CreateComponent("Projectile");
    projectile->SetSpeed(100.0f);
    projectile->SetRange(400.0f);
	projectile->SetDirection(direction);


}
