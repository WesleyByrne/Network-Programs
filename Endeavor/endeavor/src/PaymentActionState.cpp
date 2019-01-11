#include "PaymentActionState.h"
#include "EndeavorGame.h"

void PaymentActionState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

PaymentActionState::PaymentActionState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

PaymentActionState::~PaymentActionState()
{}

void PaymentActionState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();
	
	EndeavorBuildingType building_type = endeavor_game->findSelectedBuildingPlayerBoard(active_player, x, y);

	bool can_make_payment = endeavor_game->canMakePaymentAction(active_player, building_type);
	//you cannot use the action to make a payment on a level 5 building (that would be stalling indefinitely)
	if (!can_make_payment || building_type == EXCHANGE || building_type == MUSEUM || building_type == PARLIAMENT)
	{
		return;
	}

	endeavor_game->makePayment(active_player, building_type);
	endeavor_game->nextPlayer();  //player has not passed yet (took an action)
	endeavor_game->changeToActionState();
}
