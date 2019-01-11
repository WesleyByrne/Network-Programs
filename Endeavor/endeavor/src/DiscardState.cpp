#include "DiscardState.h"
#include "EndeavorGame.h"

void DiscardState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

DiscardState::DiscardState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

DiscardState::~DiscardState()
{
	endeavor_game = NULL;
}

void DiscardState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();
	uint8 player_board_loc = endeavor_game->findSelectedCardToDiscard(active_player, x, y);

	if (player_board_loc > 0)
	{
		endeavor_game->discard(active_player, player_board_loc);
	}
	
	if(!endeavor_game->mustDiscard(active_player))
	{
		endeavor_game->changeToActionState();
		endeavor_game->nextPlayerAfterPass();
	}
}
