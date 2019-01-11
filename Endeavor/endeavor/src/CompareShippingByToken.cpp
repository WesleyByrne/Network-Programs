#include "CompareShippingByToken.h"
#include "EndeavorGame.h"

CompareShippingByToken::CompareShippingByToken(EndeavorGame* game, EndeavorTokenType* order)
{
   sort_order = order;
   endeavor_game = game;
}

CompareShippingByToken::~CompareShippingByToken()
{}

int CompareShippingByToken::findRankFromTokenID(EndeavorTokenType token_id)
{
   for (int i = 0; i < 8; i++)
   {
      if (sort_order[i] == token_id)
      {
         return i + 1;
      }
   }
   
   return 9; 
}

int CompareShippingByToken::compare(Ship* ship_1, Ship* ship_2)
{
	EndeavorTokenType ship_1_token = (EndeavorTokenType) ship_1->getTokenID();
	EndeavorTokenType ship_2_token = (EndeavorTokenType) ship_2->getTokenID();

	uint8 ship_1_rank = findRankFromTokenID(ship_1_token);
	uint8 ship_2_rank = findRankFromTokenID(ship_2_token);
   
   //ascending order by token rank
   int token_diff = (int) (ship_1_rank - ship_2_rank);
   if (token_diff != 0) return token_diff;
   
   EndeavorRegionType ship_1_region = ship_1->getRegionType();
   EndeavorRegionType ship_2_region = ship_2->getRegionType();
   
   //uint8 ship_lane_1_spaces_left = endeavor_game->getNumOpenRegularLocations(ship_1_region);
   //uint8 ship_lane_2_spaces_left = endeavor_game->getNumOpenRegularLocations(ship_2_region);
   
   uint8 ship_lane_1_player_presence = endeavor_game->getActivePlayerShippingPresence(ship_1_region);
   uint8 ship_lane_2_player_presence = endeavor_game->getActivePlayerShippingPresence(ship_2_region);

   //descending order by presence in the shipping lane
   int presence_diff = (int) (ship_lane_2_player_presence - ship_lane_1_player_presence);
	return presence_diff;
}
