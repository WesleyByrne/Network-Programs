#include "OccupyOrDrawState.h"
#include "EndeavorGame.h"

void OccupyOrDrawState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

OccupyOrDrawState::OccupyOrDrawState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

OccupyOrDrawState::~OccupyOrDrawState()
{}

void OccupyOrDrawState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();
	uint8 num_workers = endeavor_game->getNumWorkers(active_player);

	uint8 city_id = endeavor_game->findSelectedCity(x, y);
	EndeavorRegionType card_id = endeavor_game->findSelectedCard(x, y);
	
	//a worker has already been used to activate the building
	//so worker requirement here is one less
	bool can_occupy_city = city_id > 0 && num_workers >= 1 && endeavor_game->canOccupyCity(active_player, city_id);
	bool can_take_card = card_id != INVALID_REGION_TYPE && num_workers >= 0 && endeavor_game->canTakeSelectedCard(active_player, card_id);
	
	if (can_occupy_city)
	{
		endeavor_game->occupyCity(active_player, city_id);
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
	}

	//check presence here only, discards are checked when the player passes
	//if the player has enough presence in the region, the topmost card is taken
	else if (can_take_card)
	{
		endeavor_game->takeSelectedCard(active_player, card_id);
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
	}
}
