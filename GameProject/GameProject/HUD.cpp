// @file: HUD.cpp
//
// @brief: This class is responsible for displaying the HUD
//
// @author: Alan
// @date: 2023/12
#include "GameCore.h"
#include "HUD.h"

IMPLEMENT_DYNAMIC_CLASS(HUD)

void HUD::Initialize() 
{
	Component::Initialize();
	KillCount = 0;
	time = 0.0f;
	timer = 0.0f;
	lastKillTime = 0.0f;
	maxHealth = 3;
	playerHealth = maxHealth;
	originalscalesize= ownerEntity->GetTransform().scale;
	alpha = 255;



	ownerEntity->GetTransform().position = Vec2(RenderSystem::Instance().GetWindowSize()) * 0.5f;
	font = (FontSprite*)ownerEntity->CreateComponent("FontSprite");
	font->SetFontColor(255, 255, 255, 255);
	font->SetFont((FontAsset*)(AssetManager::Get().GetAsset("specimen-VT323")));
	font->SetText("Time: 300s | Kills: 10| Health: 3");



}

void HUD::Update( ) 
{
	Vec2 temp = ownerEntity->GetTransform().position;
	LOG(temp.x<<"<<<"<<temp.y)
	time += Time::Instance().DeltaTime();
	
	ownerEntity->GetTransform().position+= Vec2(0.0f, -1.0f);
	alpha -= 0.3;
	font->SetFontColor(255, 255, 255, alpha);
	// You can also decide when to hide the HUD here
	if (timer - lastKillTime > visibilityThreshold)
	{
		SetInvisible();
	}
}

void HUD::Load(json::JSON& node)
{


}

void HUD::setKillCount(int count) {
	KillCount = count;
	// Update the HUD display to show the new kill count
}

int HUD::getKillCount() const {
	return KillCount;
}

void HUD::setTime(float t) {
	time = t;
}

float HUD::getTime() const {
	return time;
}

void HUD::SetPlayerHealth(int health) 
{
	playerHealth = health;
}
void HUD::ShowKillCount(Vec2 transform) 
{
	lastKillTime = timer;
	ownerEntity->GetTransform().scale= originalscalesize;
	ownerEntity->GetTransform().position = transform;

	alpha = 255;
	std::string hudText = "Time: " + std::to_string(static_cast<int>(time)) + "s | Kills: " + std::to_string(KillCount);
	font->SetText(hudText);
}
void HUD::ShowHealth(Vec2 transform) 
{
	lastKillTime = timer;
	ownerEntity->GetTransform().scale= originalscalesize;
	ownerEntity->GetTransform().position = transform;
	alpha = 255;

	std::string hudText =  "Health: " + std::to_string(playerHealth);
	font->SetText(hudText);
}

void HUD::SetInvisible() 
{
	ownerEntity->GetTransform().scale= Vec2(0.0f, 0.0f);
}


