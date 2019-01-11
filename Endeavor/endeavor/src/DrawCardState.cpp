#include "DrawCardState.h"
#include "EndeavorGame.h"

void DrawCardState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

DrawCardState::DrawCardState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

DrawCardState::~DrawCardState()
{}

void DrawCardState::mouseClicked(uint32 x, uint32 y)
{	
	uint8 active_player = endeavor_game->getActivePlayer();
	EndeavorRegionType card_id = endeavor_game->findSelectedCard(x, y);  //the card id is the region that the card is in (region 8 is the slavery cards)

	if (card_id == INVALID_REGION_TYPE) return;

	//check presence here only, discards are checked when the player passes
	//if the player has enough presence in the region, the topmost card is taken
	bool can_take_card = endeavor_game->canTakeSelectedCard(active_player, card_id);

	if (can_take_card)
	{
		endeavor_game->takeSelectedCard(active_player, card_id);
		
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
	}
}
