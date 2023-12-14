#include "GameCore.h"
#include "MainMenu.h"
#include "FontSprite.h"
IMPLEMENT_DYNAMIC_CLASS(MainMenu)

void MainMenu::Initialize()
{
	Component::Initialize();
	is_playing_audio = false;
	sound_timer= sound_delay;
	ownerEntity->GetTransform().position= Vec2(RenderSystem::Instance().GetWindowSize()) * 0.5f;
	font = (FontSprite*)ownerEntity->CreateComponent("FontSprite");
	font->SetFontColor(255,255,255,255);
	font->SetFont((FontAsset*)(AssetManager::Get().GetAsset("specimen-VT323")));
	font->SetText("Enter The Dungeon");
	button_rect = font->GetRect();
	original_scale= font->GetOwner()->GetTransform().scale;
	position = ownerEntity->GetTransform().position;
	LOG(button_rect.x<<":"<<button_rect.y);
}
void MainMenu::Update() {
	sound_timer -= Time::Instance().DeltaTime();
	HandleMouseInput();


}

void MainMenu::HandleMouseInput()
{
	// Get the mouse's current position
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	// Check if the mouse is over the button
	bool isMouseOver = (mouseX >= position.x &&
		mouseX <= position.x + button_rect.w &&
		mouseY >= position.y &&
		mouseY <= position.y + button_rect.h);

	// Check for mouse button click event
	if (isMouseOver && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		// Handle button click (e.g., call a function)
		ButtonClickFunction(); // Replace with your actual function call
	}

	// Update button appearance based on mouse hover
	if (isMouseOver)
	{
		// Render the button with a larger size and a different color
		font->SetFontColor(100,120,130,255);
		font->GetOwner()->GetTransform().scale = Vec2(0.4f, 0.4f);
	}
	else
	{
		// Reset the button's size and color
		font->GetOwner()->GetTransform().scale = original_scale;
		font->SetFontColor(255,255,255,255); // Restore the original color
	}
}
void MainMenu::ButtonClickFunction()
{
	switch (button)
	{
	case ButtonType::Play:
	{
		Scene* current_scene = SceneManager::Get().GetActiveScene();
		if (SceneManager::Get().SetActiveScene(scene_to_load))
		{
			current_scene->isEnabled = false;
		}
		break;
	}
	case ButtonType::Quit:
	{
		SDL_Event quit_event;
		quit_event.type = SDL_QUIT;
		SDL_PushEvent(&quit_event);
		break;
	}
	case ButtonType::Load:
	{
		Scene* current_scene = SceneManager::Get().GetActiveScene();
		if (SceneManager::Get().SetActiveScene(scene_to_load))
		{
			current_scene->isEnabled = false;
		}
		break;
	}
	default:
		break;
	}

}
void MainMenu::Load(json::JSON& node)
{
	Component::Load(node);
	if (node.hasKey("SoundDelay"))
	{
		sound_delay = static_cast<float>(node.at("SoundDelay").ToFloat());
	}

	if (node.hasKey("SceneToLoad"))
	{
		scene_to_load = GetHashCode(node.at("SceneToLoad").ToString().c_str());
	}

	if (node.hasKey("Sound"))
	{
		const std::string sound_asset_guid = node["Sound"].ToString();
		sound_fx = (SoundAsset*)(AssetManager::Get().GetAsset(sound_asset_guid));
	}

	if (node.hasKey("SceneLoadDelay"))
	{
		scene_load_delay = static_cast<float>(node.at("SceneLoadDelay").ToFloat());
	}
	if (node.hasKey("Buttontype"))
	{
		std::string buttonTypeStr = node["Buttontype"].ToString();
		if (buttonTypeStr == "Play")
		{
			button = ButtonType::Play;
		}
		else if (buttonTypeStr == "Quit")
		{
			button = ButtonType::Quit;
		}
		else if (buttonTypeStr == "Load")
		{
			button = ButtonType::Load;
		}

	}
}