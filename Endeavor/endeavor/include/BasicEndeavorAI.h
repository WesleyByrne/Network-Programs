#if !defined BasicEndeavor_AI
#define BasicEndeavor_AI

#include "EndeavorAI.h"
#include "EndeavorGame.h"

#include "ListArray.h"

#include "CompareCitiesByToken.h"
#include "CompareShippingByToken.h"
#include "CompareCardsByLevel.h"
#include "CompareBuildingsForPayment.h"

class Building;
class City;
class Ship;

class BasicEndeavorAI : public EndeavorAI
{
   private:
      EndeavorGame* endeavor_game;
	  
	  EndeavorTokenType* city_token_priority;
	  EndeavorTokenType* ship_token_priority;
	  EndeavorBuildingType* building_payment_priority;
	  EndeavorBuildingType* building_select_priority;
	  EndeavorActionType* action_priority;
	  
	  bool considerOccupy(uint8* action_params, bool enough_workers, bool can_use_token, CSC1310::ListArray<City>* possible_cities, CompareCitiesByToken* city_comp, uint8* unactivated_building_ids, uint8 num_unactivated_buildings);
	  bool considerShip(uint8* action_params, bool enough_workers, bool can_use_token, CSC1310::ListArray<Ship>* possible_shipping, CompareShippingByToken* ship_comp, uint8* unactivated_building_ids, uint8 num_unactivated_buildings);
	  bool considerDraw(uint8* action_params, uint8 player_id, bool enough_workers, bool can_use_ship_draw_token, bool can_use_occupy_draw_token, CSC1310::ListArray<Card>* possible_draw, CompareCardsByLevel* card_comp, uint8* unactivated_building_ids, uint8 num_unactivated_buildings);
      bool considerAttack(uint8* action_params, bool enough_workers, bool can_use_token, CSC1310::ListArray<City>* possible_cities, CompareCitiesByToken* city_comp, uint8* unactivated_building_ids, uint8 num_unactivated_buildings);
      bool considerPayment(uint8* action_params, bool enough_workers, bool can_use_token, CSC1310::ListArray<Building>* activated_buildings, CompareBuildingsForPayment* building_payment_comp, uint8* unactivated_building_ids, uint8 num_unactivated_buildings);
   
   public:
      BasicEndeavorAI(EndeavorGame* game, EndeavorTokenType* city_token_priority, EndeavorTokenType* ship_token_priority, EndeavorBuildingType* building_payment_priority, EndeavorBuildingType* building_select_priority, EndeavorActionType* action_priority);
      virtual ~BasicEndeavorAI();
	  
      virtual uint8 selectBuilding(uint8 player_id);
      virtual uint8* makePayments(uint8& num_payments, uint8 player_id);
      virtual uint8* selectAction(uint8 player_id);
      //virtual uint8 discard(uint8 player_id);
};

#endif
