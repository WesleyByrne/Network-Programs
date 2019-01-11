#include "OccupyState.h"
#include "EndeavorGame.h"

void OccupyState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{

}

OccupyState::OccupyState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

OccupyState::~OccupyState()
{}

void OccupyState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();
	uint8 city_id = endeavor_game->findSelectedCity(x, y);  

	if (city_id == 0) return;
	if (!endeavor_game->canOccupyCity(active_player, city_id)) return;

	endeavor_game->occupyCity(active_player, city_id);
	  
	endeavor_game->nextPlayer();  //player has not passed yet (took an action)
	endeavor_game->changeToActionState();
}
