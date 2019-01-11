#include "OccupyOrAttackState.h"
#include "EndeavorGame.h"

void OccupyOrAttackState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

OccupyOrAttackState::OccupyOrAttackState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

OccupyOrAttackState::~OccupyOrAttackState()
{}

void OccupyOrAttackState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();
	uint8 num_workers = endeavor_game->getNumWorkers(active_player);

	uint8 city_id = endeavor_game->findSelectedCity(x, y);
	
	//a worker has already been used to activate the building
	//so worker requirement here is one less
	bool can_occupy_city = city_id > 0 && num_workers >= 1 && endeavor_game->canOccupyCity(active_player, city_id);
	bool can_attack_city = city_id > 0 && num_workers >= 2 && endeavor_game->canAttackCity(active_player, city_id);

	if (can_occupy_city)
	{
		endeavor_game->occupyCity(active_player, city_id);
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
	}
	else if (can_attack_city)
	{
		endeavor_game->attackCity(active_player, city_id);
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
	}
}
