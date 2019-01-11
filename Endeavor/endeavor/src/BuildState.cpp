#include "BuildState.h"
#include "EndeavorGame.h"

BuildState::BuildState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

BuildState::~BuildState()
{
	endeavor_game = NULL;
}

void BuildState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
	uint8 building_id = ai->selectBuilding(ai_id);

	Building* selected_building = endeavor_game->removeBuilding((EndeavorBuildingType) building_id);
	endeavor_game->takeBuilding(ai_id, selected_building);
	endeavor_game->populationGrowth(ai_id);
	endeavor_game->nextPlayerAfterPass();
}

void BuildState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();
	
	uint8 lowest_level_available = endeavor_game->getLowestLevelAvailable();
	//did the player click on a building that they can actually build?
	EndeavorBuildingType building_type = endeavor_game->findSelectedBuilding(x, y);
	
	//make sure that the action is legal before performing the action
	bool can_take_building = false;
	if (building_type != INVALID_BUILDING_TYPE)
	{
		can_take_building = endeavor_game->canTakeBuilding(active_player, building_type, lowest_level_available);
	}
	
	//looks okay, perform the action
	if (can_take_building)
	{
		Building* selected_building = endeavor_game->removeBuilding(building_type);
		endeavor_game->takeBuilding(active_player, selected_building);
		endeavor_game->populationGrowth(active_player);
		endeavor_game->nextPlayerAfterPass();
	}
}
