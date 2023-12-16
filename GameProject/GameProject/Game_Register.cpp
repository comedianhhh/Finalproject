#include "GameCore.h"

#include "Player.h"
#include "Enemy.h"
#include "GameOver.h"
#include "Projectile.h"
#include "SpawnerComponent.h"
#include "MainMenu.h"
#include "HUD.h"
#include "Loot.h"
void GameRegisterClasses()
{
	REGISTER_TYPECLASS(Player)
	REGISTER_TYPECLASS(Enemy)
	REGISTER_TYPECLASS(GameOver)
	REGISTER_TYPECLASS(Projectile)
	REGISTER_TYPECLASS(SpawnerComponent)
	REGISTER_TYPECLASS(MainMenu)
	REGISTER_TYPECLASS(HUD)
	REGISTER_TYPECLASS(Loot)
}