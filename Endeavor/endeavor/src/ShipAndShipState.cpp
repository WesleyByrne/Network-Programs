#include "ShipAndShipState.h"
#include "EndeavorGame.h"

void ShipAndShipState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

ShipAndShipState::ShipAndShipState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
	action_region = INVALID_REGION_TYPE;
	first_ship = false;
	second_ship = false;
}

ShipAndShipState::~ShipAndShipState()
{}

void ShipAndShipState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();
	uint8 num_workers = endeavor_game->getNumWorkers(active_player);

	EndeavorRegionType ship_region = endeavor_game->findSelectedShip(x, y);

	bool can_ship = (ship_region != INVALID_REGION_TYPE) && (action_region == INVALID_REGION_TYPE || (action_region == ship_region && first_ship));

	//player has not already shipped and has selected a valid shipping location
	if (can_ship)
	{
		if (first_ship) second_ship = true;
		else first_ship = true;
		
		action_region = ship_region;
		//process ship
		endeavor_game->ship(active_player, ship_region);
		
		if (endeavor_game->canAssignGovernorCard(ship_region))
		{
			uint8 governor_id = endeavor_game->assignGovernorCard(ship_region);
			endeavor_game->moveGovernorCardToPlayer(governor_id, ship_region);
		}
	}

	//player completed both actions, so it's the next player's turn
	if (first_ship && second_ship)
	{
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
		
		//reset for a later player
		action_region = INVALID_REGION_TYPE;
		first_ship = false;
		second_ship = false;
		return;
	}
	
	//player could only perform one of the two actions
	//the player ran out of workers
	if (action_region != INVALID_REGION_TYPE)
	{
		num_workers = endeavor_game->getNumWorkers(active_player);
		if (num_workers == 0)
		{
			endeavor_game->nextPlayer();  //player has not passed yet (took an action)
			endeavor_game->changeToActionState();
			
			action_region = INVALID_REGION_TYPE;
			first_ship = false;
			second_ship = false;
			return;
		}
	}
}
