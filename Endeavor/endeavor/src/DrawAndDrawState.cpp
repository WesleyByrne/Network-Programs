#include "DrawAndDrawState.h"
#include "EndeavorGame.h"

void DrawAndDrawState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

DrawAndDrawState::DrawAndDrawState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
	action_region = INVALID_REGION_TYPE;
	first_draw = false;
	second_draw = false;
}

DrawAndDrawState::~DrawAndDrawState()
{}

void DrawAndDrawState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();
	uint8 num_workers = endeavor_game->getNumWorkers(active_player);

	EndeavorRegionType draw_region = endeavor_game->findSelectedCard(x, y);

	bool can_draw = (draw_region != INVALID_REGION_TYPE) && (action_region == INVALID_REGION_TYPE || (action_region == draw_region && first_draw));
	can_draw = can_draw && endeavor_game->canTakeSelectedCard(active_player, draw_region);

	if (can_draw)
	{
		if (first_draw) second_draw = true;
		else first_draw = true;
		
		action_region = draw_region;
		endeavor_game->takeSelectedCard(active_player, draw_region);
	}

	//player completed both actions, so it's the next player's turn
	if (first_draw && second_draw)
	{
		endeavor_game->nextPlayer();  //player has not passed yet (took an action)
		endeavor_game->changeToActionState();
		
		//reset for a later player
		action_region = INVALID_REGION_TYPE;
		first_draw = false;
		second_draw = false;
		return;
	}
	
	//player could only perform one of the two actions
	//the player cannot draw in the region in which they have already drawn a card
	if (action_region != INVALID_REGION_TYPE)
	{
		bool can_draw_in_region = endeavor_game->canTakeSelectedCard(active_player, action_region);
		if (!can_draw_in_region)
		{
			endeavor_game->nextPlayer();  //player has not passed yet (took an action)
			endeavor_game->changeToActionState();
			
			action_region = INVALID_REGION_TYPE;
			first_draw = false;
			second_draw = false;
			return;
		}
	}
}
