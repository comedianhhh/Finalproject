#include "GameCore.h"

#include "Player.h"
#include "Enemy.h"
#include "GameOver.h"

void GameRegisterClasses()
{
	REGISTER_TYPECLASS(Player)
	REGISTER_TYPECLASS(Enemy)
	REGISTER_TYPECLASS(GameOver)
}