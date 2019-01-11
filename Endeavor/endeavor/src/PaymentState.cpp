#include "PaymentState.h"
#include "EndeavorGame.h"

void PaymentState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
	uint8 num_payments;
	uint8* building_ids = ai->makePayments(num_payments, ai_id);
	for (int i = 0; i < num_payments; i++)
	{
		endeavor_game->makePayment(ai_id, (EndeavorBuildingType) building_ids[i]);
	}
	delete[] building_ids;
	endeavor_game->nextPlayerAfterPass();
}

PaymentState::PaymentState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

PaymentState::~PaymentState()
{
	endeavor_game = NULL;
}

void PaymentState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();

	EndeavorBuildingType building_type = endeavor_game->findSelectedBuildingPlayerBoard(active_player, x, y);

	bool can_make_payment = endeavor_game->canMakePayment(active_player, building_type);
	if (!can_make_payment)
	{
		return;
	}

	endeavor_game->makePayment(active_player, building_type);

	//automatically move on to the next player as no more payments can be made by this player
	bool can_make_any_payments = endeavor_game->canMakeAnyPayments(active_player);
	if (!can_make_any_payments)
	{
		endeavor_game->nextPlayerAfterPass();
	}
}
