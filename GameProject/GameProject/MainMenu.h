// @file: MainMenu.h
//
// @brief: MainMenu class, used to display the main menu of the game
//
// @author: Alan
// @date: 2023/12

#pragma once
#ifndef _MAINMENU_H
#define _MAINMENU_H
#include "GameCore.h"
#include "FontSprite.h"
class MainMenu final : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(MainMenu, Component)

public:
	void Initialize() override;
	void Update() override;
	void Load(json::JSON&) override;

private:
	float sound_delay = 5.0f;
	float sound_timer = 0;
	float scene_load_delay = 10;

	STRCODE scene_to_load = -1;
	SoundAsset* sound_fx = nullptr;
	bool is_playing_audio = false;

public:
	enum class ButtonType
	{
		Play,
		Quit,
		Options,
		Load
	};
	ButtonType button;
	FontSprite* font = nullptr;
	FontAsset* font_asset;
	SDL_Rect button_rect;
	Vec2 position;
	// Function to handle button clicks
	void HandleMouseInput();
	void ButtonClickFunction();
	int current_index = 0;
	Vec2 original_scale;

};



#endif // !_MAINMENU_H