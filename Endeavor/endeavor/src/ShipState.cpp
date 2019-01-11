#include "ShipState.h"
#include "EndeavorGame.h"

void ShipState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

ShipState::ShipState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

ShipState::~ShipState()
{}

void ShipState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();

	//returns INVALID_REGION_TYPE unless player clicks on the next available shipping lane position (ship_cursor)
	EndeavorRegionType region_type = endeavor_game->findSelectedShip(x, y);

	if (region_type != INVALID_REGION_TYPE)
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
}
