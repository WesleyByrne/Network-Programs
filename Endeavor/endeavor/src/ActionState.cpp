#include "ActionState.h"
#include "EndeavorGame.h"

void ActionState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
	uint8* action_elements = ai->selectAction(ai_id);
	
	if (action_elements[0] == (int) OCCUPY_ACTION)  //occupy action
	{
		EndeavorBuildingType building_type = (EndeavorBuildingType) action_elements[1];
		uint8 city_id = action_elements[2];
		
		endeavor_game->activateBuilding(ai_id, building_type);
		endeavor_game->occupyCity(ai_id, city_id);
		
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
	}
	
	else if (action_elements[0] == (int) OCCUPY_TOKEN_ACTION)  //occupy using token action
	{
		EndeavorBuildingType action_token_type = (EndeavorBuildingType) action_elements[1];
		uint8 city_id = action_elements[2];
		
		endeavor_game->useActionToken(ai_id, action_token_type);
		endeavor_game->occupyCity(ai_id, city_id);
		
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
	}
	
	else if (action_elements[0] == (int) SHIP_ACTION)  //ship action
	{
		EndeavorBuildingType building_type = (EndeavorBuildingType) action_elements[1];
		EndeavorRegionType region_type = (EndeavorRegionType) action_elements[2];
		
		endeavor_game->activateBuilding(ai_id, building_type);
		endeavor_game->ship(ai_id, region_type);
		
		if (endeavor_game->canAssignGovernorCard(region_type))
		{
			uint8 governor_id = endeavor_game->assignGovernorCard(region_type);
			endeavor_game->moveGovernorCardToPlayer(governor_id, region_type);
		}
		
		//if the player activates the CARTOGRAPHER, they can ship twice to the same region
		//if they have enough workers
		if (building_type == CARTOGRAPHER && endeavor_game->getNumWorkers(ai_id) >= 1)
		{
		PRINT("CARTOGRAPHER")
			endeavor_game->ship(ai_id, region_type);
			if (endeavor_game->canAssignGovernorCard(region_type))
			{
				uint8 governor_id = endeavor_game->assignGovernorCard(region_type);
				endeavor_game->moveGovernorCardToPlayer(governor_id, region_type);
			}
		}
		
		endeavor_game->nextPlayer();  
		endeavor_game->changeToActionState();
	}
	
	else if (action_elements[0] == (int) SHIP_TOKEN_ACTION)  //ship using token action
	{
		EndeavorBuildingType action_token_type = (EndeavorBuildingType) action_elements[1];
		EndeavorRegionType region_type = (EndeavorRegionType) action_elements[2];
		
		endeavor_game->useActionToken(ai_id, action_token_type);
		endeavor_game->ship(ai_id, region_type);
		
		if (endeavor_game->canAssignGovernorCard(region_type))
		{
			uint8 governor_id = endeavor_game->assignGovernorCard(region_type);
			endeavor_game->moveGovernorCardToPlayer(governor_id, region_type);
		}
		
		endeavor_game->nextPlayer();  
		endeavor_game->changeToActionState();
	}
	
	else if (action_elements[0] == (int) DRAW_ACTION)  //draw action
	{
		EndeavorBuildingType building_type = (EndeavorBuildingType) action_elements[1];
		EndeavorRegionType region_type = (EndeavorRegionType) action_elements[2];
		
		endeavor_game->activateBuilding(ai_id, building_type);
		endeavor_game->takeSelectedCard(ai_id, region_type);
		
		//if the player activates the TRADE_OFFICE, they can take two cards
		//from the same region if they have enough presence
		if (building_type == TRADE_OFFICE && endeavor_game->canTakeSelectedCard(ai_id, region_type))
		{
		PRINT("TRADE OFFICE")
			endeavor_game->takeSelectedCard(ai_id, region_type);
		}
		
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
	}
	
	else if (action_elements[0] == (int) DRAW_TOKEN_ACTION)  //draw action using a token
	{
		EndeavorBuildingType action_token_type = (EndeavorBuildingType) action_elements[1];
		EndeavorRegionType region_type = (EndeavorRegionType) action_elements[2];
		
		endeavor_game->useActionToken(ai_id, action_token_type);
		endeavor_game->takeSelectedCard(ai_id, region_type);
		
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
	}
	
	else if (action_elements[0] == (int) ATTACK_ACTION)  //attack action
	{
		EndeavorBuildingType building_type = (EndeavorBuildingType) action_elements[1];
		uint8 city_id = action_elements[2];
		
		endeavor_game->activateBuilding(ai_id, building_type);
		endeavor_game->attackCity(ai_id, city_id);
		
		endeavor_game->nextPlayer();  
		endeavor_game->changeToActionState();
	}
	
	else if (action_elements[0] == (int) ATTACK_TOKEN_ACTION)  //attack token action
	{
		EndeavorBuildingType action_token_type = (EndeavorBuildingType) action_elements[1];
		uint8 city_id = action_elements[2];
		
		endeavor_game->useActionToken(ai_id, action_token_type);
		endeavor_game->attackCity(ai_id, city_id);
		
		endeavor_game->nextPlayer();  
		endeavor_game->changeToActionState();
	}
	
	else if (action_elements[0] == (int) PAYMENT_ACTION)  //payment action
	{
		EndeavorBuildingType building_type_activate = (EndeavorBuildingType) action_elements[1];
		EndeavorBuildingType building_type_deactivate = (EndeavorBuildingType) action_elements[2];
		
		endeavor_game->activateBuilding(ai_id, building_type_activate);
		endeavor_game->makePayment(ai_id, building_type_deactivate);
		
		endeavor_game->nextPlayer();  
		endeavor_game->changeToActionState();
	}
	
	else if (action_elements[0] == (int) PAYMENT_TOKEN_ACTION)  //payment token action
	{
		EndeavorBuildingType action_token_type = (EndeavorBuildingType) action_elements[1];
		EndeavorBuildingType building_type_unactivate = (EndeavorBuildingType) action_elements[2];
		
		endeavor_game->useActionToken(ai_id, action_token_type);
		endeavor_game->makePayment(ai_id, building_type_unactivate);
		
		endeavor_game->nextPlayer();  
		endeavor_game->changeToActionState();
	}
	
	else //player passed
	{
		while(endeavor_game->mustDiscard(ai_id))
		{
			//int num_cards = endeavor_game->getNumCardsOnPlayerBoard(ai_id);
			uint8 default_card_to_discard = endeavor_game->getDefaultCardToDiscard(ai_id);
			PRINT("discarding")
			PRINT((int) default_card_to_discard)
			endeavor_game->discard(ai_id, default_card_to_discard);
		}
		
		endeavor_game->nextPlayerAfterPass();
	}

	delete[] action_elements;
}

ActionState::ActionState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

ActionState::~ActionState()
{
	endeavor_game = NULL;
}

void ActionState::mouseClicked(uint32 x, uint32 y)
{
	//check for pass
	uint8 active_player = endeavor_game->getActivePlayer();
	bool player_pass = endeavor_game->doesPlayerPass(x, y);

	if (player_pass)
	{
		if (endeavor_game->mustDiscard(active_player))
		{
			endeavor_game->changeToDiscardState();
			return;
		}
		//wait for everyone to pass before moving back to the build state and the next round
		endeavor_game->nextPlayerAfterPass();
		return;
	}
	
	uint8 num_workers = endeavor_game->getNumWorkers(active_player);
	EndeavorBuildingType building_type = endeavor_game->findSelectedBuildingPlayerBoard(active_player, x, y);

	//action tokens are not activated
	if ((int) building_type <= 15)
	{
		//find at least one building that has not been activated with the provided building id
		bool can_activate = endeavor_game->canActivateBuilding(active_player, building_type);
		if (!can_activate) return;
	}

	//at least one building of the correct type has not been activated
	//need to check to see if there are any available locations to occupy

	if (building_type == COLONIAL_HOUSE && num_workers >= 2 && endeavor_game->canOccupyInAnyRegion(active_player))  //occupy (colonial house)
	{
		endeavor_game->activateBuilding(active_player, building_type);
		endeavor_game->changeToState("occupy");
		//endeavor_game->changeToOccupyState();
	}
	
	else if (building_type == SHIPYARD && num_workers >= 2 && endeavor_game->canShipInAnyRegion(active_player))
	{
		endeavor_game->activateBuilding(active_player, building_type);
		endeavor_game->changeToState("ship");
		//endeavor_game->changeToShipState();
	}
	
	//need to check to see if there are any cards that the player can draw (anywhere)
	else if (building_type == MARKET && num_workers >= 1 && endeavor_game->canDrawFromAnyRegion(active_player))
	{
		endeavor_game->activateBuilding(active_player, building_type);
		endeavor_game->changeToState("draw");
		//endeavor_game->changeToDrawCardState();
	}
	
	else if (building_type == BARRACKS && num_workers >= 3 && endeavor_game->canAttackInAnyRegion(active_player))
	{
		endeavor_game->activateBuilding(active_player, building_type);
		endeavor_game->changeToState("attack");
		//endeavor_game->changeToAttackState();
	}
	
	else if (building_type == GUILD_HALL)
	{
		if (num_workers >= 2 && endeavor_game->canShipInAnyRegion(active_player))
		{
			endeavor_game->activateBuilding(active_player, building_type);
			endeavor_game->changeToState("ship_or_draw");
			//endeavor_game->changeToShipOrDrawState();
		}
		else if (num_workers >= 1 && endeavor_game->canDrawFromAnyRegion(active_player))
		{
			endeavor_game->activateBuilding(active_player, building_type);
			endeavor_game->changeToState("ship_or_draw");
			//endeavor_game->changeToShipOrDrawState();
		}
	}
	
	else if (building_type == FORTRESS)
	{
		if (num_workers >= 3 && endeavor_game->canAttackInAnyRegion(active_player))
		{
			endeavor_game->activateBuilding(active_player, building_type);
			endeavor_game->changeToState("occupy_or_attack");
			//endeavor_game->changeToOccupyOrAttackState();
		}
		else if (num_workers >= 2 && endeavor_game->canOccupyInAnyRegion(active_player))
		{
			endeavor_game->activateBuilding(active_player, building_type);
			endeavor_game->changeToState("occupy_or_attack");
			//endeavor_game->changeToOccupyOrAttackState();
		}
	}
	
	else if (building_type == DOCKS)
	{
		if (num_workers >= 2 && endeavor_game->canShipInAnyRegion(active_player))
		{
			endeavor_game->activateBuilding(active_player, building_type);
			endeavor_game->changeToState("ship_and_occupy");
			//endeavor_game->changeToShipAndOccupyState();
		}
	}
	
	else if (building_type == CARTOGRAPHER)
	{
		if (num_workers >= 2 && endeavor_game->canShipInAnyRegion(active_player))
		{
			endeavor_game->activateBuilding(active_player, building_type);
			endeavor_game->changeToState("ship_and_ship");
			//endeavor_game->changeToShipAndShipState();
		}
	}
	
	else if (building_type == TRADE_OFFICE)
	{
		if (num_workers >= 1 && endeavor_game->canDrawFromAnyRegion(active_player))
		{
			endeavor_game->activateBuilding(active_player, building_type);
			endeavor_game->changeToState("draw_and_draw");
			//endeavor_game->changeToDrawAndDrawState();
		}
	}
	
	else if (building_type == EXCHANGE || building_type == MUSEUM || building_type == PARLIAMENT)
	{
		if (num_workers >= 1 && endeavor_game->canTakePaymentAction(active_player))
		{
			endeavor_game->activateBuilding(active_player, building_type);
			endeavor_game->changeToState("payment_action");
			//endeavor_game->changeToPaymentActionState();
		}
	}
	
	else if (building_type == SHIP_OR_DRAW_TOKEN)
	{
		if (num_workers >= 1 && endeavor_game->canShipInAnyRegion(active_player))
		{
			endeavor_game->useActionToken(active_player, building_type);
			endeavor_game->changeToState("ship_or_draw");
			//endeavor_game->changeToShipOrDrawState();
		}
		else if (num_workers >= 0 && endeavor_game->canDrawFromAnyRegion(active_player))
		{
			endeavor_game->useActionToken(active_player, building_type);
			endeavor_game->changeToState("ship_or_draw");
			//endeavor_game->changeToShipOrDrawState();
		}
	}
	
	else if (building_type == OCCUPY_OR_DRAW_TOKEN)
	{
		if (num_workers >= 1 && endeavor_game->canOccupyInAnyRegion(active_player))
		{
			endeavor_game->useActionToken(active_player, building_type);
			endeavor_game->changeToState("occupy_or_draw");
			//endeavor_game->changeToOccupyOrDrawState();
		}
		else if (num_workers >= 0 && endeavor_game->canDrawFromAnyRegion(active_player))
		{
			endeavor_game->useActionToken(active_player, building_type);
			endeavor_game->changeToState("occupy_or_draw");
			//endeavor_game->changeToOccupyOrDrawState();
		}
	}
	
	else if (building_type == ATTACK_TOKEN)
	{
		if (num_workers >= 2 && endeavor_game->canAttackInAnyRegion(active_player))
		{
			endeavor_game->useActionToken(active_player, building_type);
			endeavor_game->changeToState("attack");
			//endeavor_game->changeToAttackState();
		}
	}
	
	else if (building_type == PAYMENT_TOKEN)
	{
		if (num_workers >= 0 && endeavor_game->canTakePaymentAction(active_player))
		{
			endeavor_game->useActionToken(active_player, building_type);
			endeavor_game->changeToState("payment_action");
			//endeavor_game->changeToPaymentActionState();
		}
	}
}
