#include "ShipOrDrawState.h"
#include "EndeavorGame.h"

void ShipOrDrawState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

ShipOrDrawState::ShipOrDrawState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

ShipOrDrawState::~ShipOrDrawState()
{}

void ShipOrDrawState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();
	uint8 num_workers = endeavor_game->getNumWorkers(active_player);

	EndeavorRegionType region_type = endeavor_game->findSelectedShip(x, y);
	EndeavorRegionType card_id = endeavor_game->findSelectedCard(x, y);

	//a worker has already been used to activate the building
	//so worker requirement here is one less
	//can always ship
	bool can_ship = region_type != INVALID_REGION_TYPE && num_workers >= 1; 
	bool can_take_card = card_id != INVALID_REGION_TYPE && num_workers >= 0 && endeavor_game->canTakeSelectedCard(active_player, card_id);
	
	if (can_ship)
	{
		endeavor_game->ship(active_player, region_type);
		
		if (endeavor_game->canAssignGovernorCard(region_type))
		{
			uint8 governor_id = endeavor_game->assignGovernorCard(region_type);
			endeavor_game->moveGovernorCardToPlayer(governor_id, region_type);
		}
		
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
