#include "ShipAndOccupyState.h"
#include "EndeavorGame.h"

void ShipAndOccupyState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

ShipAndOccupyState::ShipAndOccupyState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
	action_region = INVALID_REGION_TYPE;
	ship = false;
	occupy = false;
}

ShipAndOccupyState::~ShipAndOccupyState()
{}

void ShipAndOccupyState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();
	uint8 num_workers = endeavor_game->getNumWorkers(active_player);
	
	EndeavorRegionType  city_region = INVALID_REGION_TYPE;
	uint8 city_id = endeavor_game->findSelectedCity(x, y);
	if (city_id > 0)
	{
		city_region = endeavor_game->getRegionWithCity(city_id);
		//assuming that the docks cannot be used in the mediterranean
		if (city_region == MEDITERRANEAN) return;
	}

	EndeavorRegionType ship_region = endeavor_game->findSelectedShip(x, y);

	bool can_ship = !ship && (ship_region != INVALID_REGION_TYPE) && (action_region == INVALID_REGION_TYPE || (action_region == ship_region && occupy));
	bool can_occupy_city = !occupy && (city_region != INVALID_REGION_TYPE) && (action_region == INVALID_REGION_TYPE || (action_region == city_region && ship));
	can_occupy_city =  can_occupy_city && endeavor_game->canOccupyCity(active_player, city_id);

	//player has not already shipped and has selected a valid shipping location
	if (can_ship)
	{
		ship = true;
		action_region = ship_region;
		//process ship
		endeavor_game->ship(active_player, ship_region);
		
		if (endeavor_game->canAssignGovernorCard(ship_region))
		{
			uint8 governor_id = endeavor_game->assignGovernorCard(ship_region);
			endeavor_game->moveGovernorCardToPlayer(governor_id, ship_region);
		}
	}
	
	//player has not already occupied and has selected a valid occupy location
	if (can_occupy_city)
	{
		occupy = true;
		action_region = city_region;
		endeavor_game->occupyCity(active_player, city_id);
	}

	//player completed both actions, so it's the next player's turn
	if (ship && occupy)
	{
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
		
		//reset for a later player
		action_region = INVALID_REGION_TYPE;
		ship = false;
		occupy = false;
		return;
	}
	
	//player could only perform one of the two actions
	//either the player ran out of workers
	//or the player cannot occupy in the region in which they have already shipped
	if (action_region != INVALID_REGION_TYPE)
	{
		bool can_occupy_in_region = endeavor_game->canOccupyInRegion(active_player, action_region);
		num_workers = endeavor_game->getNumWorkers(active_player);
		if (!can_occupy_in_region || num_workers == 0)
		{
			endeavor_game->nextPlayer();  //player has not passed yet (took an action)
			endeavor_game->changeToActionState();
			
			action_region = INVALID_REGION_TYPE;
			ship = false;
			occupy = false;
			return;
		}
	}
}
