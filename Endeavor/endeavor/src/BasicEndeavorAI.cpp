#include "BasicEndeavorAI.h"

#include "ListArrayIterator.h"
#include "PQHeapComparator.h"

#include "Building.h"
#include "City.h"

//does this need to be here or not? (get unpredictable link errors)
//EndeavorGame* BasicEndeavorAI::endeavor_game = NULL;

BasicEndeavorAI::BasicEndeavorAI(EndeavorGame* game, EndeavorTokenType* city_priority, EndeavorTokenType* ship_priority, EndeavorBuildingType* build_payment_priority, EndeavorBuildingType* build_select_priority, EndeavorActionType* act_priority) : EndeavorAI()
{
    endeavor_game = game;
	
	city_token_priority = city_priority;
	ship_token_priority = ship_priority;
	building_payment_priority = build_payment_priority;
	building_select_priority = build_select_priority;
	action_priority = act_priority;
}

BasicEndeavorAI::~BasicEndeavorAI()
{
	delete[] city_token_priority;
	delete[] ship_token_priority;
	delete[] building_payment_priority;
	delete[] building_select_priority;
	delete[] action_priority;
}

uint8* BasicEndeavorAI::makePayments(uint8& num_payments, uint8 player_id)
{
   uint8 num_activated = endeavor_game->getNumActivatedBuildings(player_id);
   num_payments = endeavor_game->getNumPayments(player_id);
   if (num_activated < num_payments)
   {
      num_payments = num_activated;
   }

   uint8* payment_building_ids = new uint8[num_payments];

   CSC1310::ListArray<Building> activated_buildings;
   endeavor_game->getActivatedBuildings(&activated_buildings, player_id);

   if (activated_buildings.size() == 0) return payment_building_ids;

   CompareBuildingsForPayment building_payment_comp(building_payment_priority);
   PQHeapComparator<Building> pq_payment(&building_payment_comp);

   CSC1310::ListArrayIterator<Building>* possible_payment_iter = activated_buildings.iterator();
   while(possible_payment_iter->hasNext())
   {
      Building* building = possible_payment_iter->next();
      pq_payment.pqInsert(building);
   }
   delete possible_payment_iter;

   int count = 0;
   while(!pq_payment.pqIsEmpty() && count < num_payments)
   {
      Building* selected_building = pq_payment.pqRemove();
      uint8 building_id = selected_building->getBuildingID();
      payment_building_ids[count] = building_id;
      count++;
   }

   //the PQ and the ListArray should be deleted automatically as they are on the stack
   return payment_building_ids;
}

bool BasicEndeavorAI::considerOccupy(uint8* action_params, bool enough_workers, bool can_use_token, CSC1310::ListArray<City>* possible_cities, CompareCitiesByToken* city_comp, uint8* unactivated_building_ids, uint8 num_unactivated_buildings)
{
	bool action_found = false;
	
	if (enough_workers || can_use_token)
   {
	   bool building_found = false;
	  if (enough_workers)
	  {
			for (int i = 0; i < num_unactivated_buildings; i++)  //0, 7, 8
			{
				if (unactivated_building_ids[i] == 0 || unactivated_building_ids[i] == 7 || unactivated_building_ids[i] == 8)
				{
					//found a building that can be used to occupy
					action_params[0] = (int) OCCUPY_ACTION;  //can occupy!
					action_params[1] = unactivated_building_ids[i];
					building_found = true;
					break;
				}
			}
	  }
	  
	  if(can_use_token && !building_found)
	  {
		  action_params[0] = (int) OCCUPY_TOKEN_ACTION;
		  action_params[1] = (int) OCCUPY_OR_DRAW_TOKEN;
		  building_found = true;
	  }
			
		if (building_found)
		{
			//now find a city to occupy
			PQHeapComparator<City> pq_city(city_comp);  //min priority queue

			CSC1310::ListArrayIterator<City>* possible_city_iter = possible_cities->iterator();
			while(possible_city_iter->hasNext())
			{
				City* city = possible_city_iter->next();
				pq_city.pqInsert(city);
			}
			delete possible_city_iter;

			if (!pq_city.pqIsEmpty())
			{
				City* best_city = pq_city.pqRemove();
				uint8 city_id = best_city->getCityID();

				action_params[2] = city_id;
				action_found = true;
			 
				std::cout << "occupy: " << (int) action_params[2] << std::endl;
				std::cout << "building: " << (int) action_params[1] << std::endl;
				std::cout << std::endl;
			}
		}
    }
	
	return action_found;
}

bool BasicEndeavorAI::considerShip(uint8* action_params, bool enough_workers, bool can_use_token, CSC1310::ListArray<Ship>* possible_shipping, CompareShippingByToken* ship_comp, uint8* unactivated_building_ids, uint8 num_unactivated_buildings)
{
	bool action_found = false;
	if (enough_workers || can_use_token)
	{
		bool building_found = false;
		if (enough_workers)
	  {
		for (int i = 0; i < num_unactivated_buildings; i++)  //2, 6, 7, 10
		{
			if (unactivated_building_ids[i] == 2 || unactivated_building_ids[i] == 6 || unactivated_building_ids[i] == 7 || unactivated_building_ids[i] == 10)
			{
				//found a building that can be used to ship
				action_params[0] = (int) SHIP_ACTION;  //can ship!
				action_params[1] = unactivated_building_ids[i];
				building_found = true;
				break;
			}
		}
	  }
		
		if(can_use_token && !building_found)
	  {
		  action_params[0] = (int) SHIP_TOKEN_ACTION;
		  action_params[1] = (int) SHIP_OR_DRAW_TOKEN;
		  building_found = true;
	  }
					
		if (building_found)
		{
			PQHeapComparator<Ship> pq_ship(ship_comp);

			CSC1310::ListArrayIterator<Ship>* possible_ship_iter = possible_shipping->iterator();
			while(possible_ship_iter->hasNext())
			{
				Ship* ship = possible_ship_iter->next();
				pq_ship.pqInsert(ship);
			}
			delete possible_ship_iter;

			if (!pq_ship.pqIsEmpty())
			{
				Ship* best_ship = pq_ship.pqRemove();
				EndeavorRegionType region_type = best_ship->getRegionType();
							
				action_params[2] = (uint8) region_type;
				action_found = true;
				
				std::cout << "ship: " << (int) action_params[2] << std::endl;
				std::cout << "building: " << (int) action_params[1] << std::endl;
				std::cout << std::endl;
			}
		}
	}
	
	return action_found;
}

bool BasicEndeavorAI::considerDraw(uint8* action_params, uint8 player_id, bool enough_workers, bool can_use_ship_draw_token, bool can_use_occupy_draw_token, CSC1310::ListArray<Card>* possible_draw, CompareCardsByLevel* card_comp, uint8* unactivated_building_ids, uint8 num_unactivated_buildings)
{
	bool action_found = false;
	if (enough_workers || can_use_ship_draw_token || can_use_occupy_draw_token )
	{
		bool building_found = false;
		if (enough_workers)
	  {
		for (int i = 0; i < num_unactivated_buildings; i++)  //1, 6, 11
		{
			if (unactivated_building_ids[i] == 1 || unactivated_building_ids[i] == 6 || unactivated_building_ids[i] == 11)
			{
				//found a building that can be used to draw
				action_params[0] = (int) DRAW_ACTION;  //can draw!
				action_params[1] = unactivated_building_ids[i];
				building_found = true;
				break;
			}
		}
	  }
		
		if(can_use_ship_draw_token && !building_found)
		{
			action_params[0] = (int) DRAW_TOKEN_ACTION;
			action_params[1] = (int) SHIP_OR_DRAW_TOKEN;
			building_found = true;
		}
		else if(can_use_occupy_draw_token && !building_found)
		{
			action_params[0] = (int) DRAW_TOKEN_ACTION;
			action_params[1] = (int) OCCUPY_OR_DRAW_TOKEN;
			building_found = true;
		}
					
		if (building_found)
		{
			PQHeapComparator<Card> pq_draw(card_comp);

			CSC1310::ListArrayIterator<Card>* possible_draw_iter = possible_draw->iterator();
			while(possible_draw_iter->hasNext())
			{
				Card* card = possible_draw_iter->next();
				pq_draw.pqInsert(card);
			}
			delete possible_draw_iter;

//ADD FEATURE
			//get the card level of the weakest current card
			//if the card that can be taken is two levels higher, take
			//that card even if the ai will then need to discard
			while (!pq_draw.pqIsEmpty())
			{
				Card* best_card = pq_draw.pqRemove();
				EndeavorRegionType region_type = best_card->getCardID();
							
				if (!endeavor_game->mustDiscardIfCardTaken(best_card, player_id))
				{
					action_params[2] = (uint8) region_type;
					action_found = true;
					
					std::cout << "card: " << (int) action_params[2] << std::endl;
					std::cout << "building: " << (int) action_params[1] << std::endl;
					std::cout << std::endl;
					break;
				}
				else if (best_card->getCardLevel() >= 3)
				{
				PRINT("taking a card and must discard!!")
					action_params[2] = (uint8) region_type;
					action_found = true;
					
					std::cout << "card: " << (int) action_params[2] << std::endl;
					std::cout << "building: " << (int) action_params[1] << std::endl;
					std::cout << std::endl;
					break;
				}
			}
		}
	}
	
	return action_found;
}

bool BasicEndeavorAI::considerAttack(uint8* action_params, bool enough_workers, bool can_use_token, CSC1310::ListArray<City>* possible_attack, CompareCitiesByToken* city_comp, uint8* unactivated_building_ids, uint8 num_unactivated_buildings)
{
	bool action_found = false;
	if (enough_workers || can_use_token)
	{
		bool building_found = false;
		if (enough_workers)
	  {
		for (int i = 0; i < num_unactivated_buildings; i++)  //5, 8
		{
			if (unactivated_building_ids[i] == 5 || unactivated_building_ids[i] == 8)
			{
				//found a building that can be used to attack
				action_params[0] = (int) ATTACK_ACTION;  //attack!
				action_params[1] = unactivated_building_ids[i];
				building_found = true;
				break;
			}
		}
	  }
		
		if(can_use_token && !building_found)
		{
			action_params[0] = (int) ATTACK_TOKEN_ACTION;
			action_params[1] = (int) ATTACK_TOKEN;
			building_found = true;
		}
		
		if(building_found)
		{
			PQHeapComparator<City> pq_attack(city_comp);

			CSC1310::ListArrayIterator<City>* possible_attack_iter = possible_attack->iterator();
			while(possible_attack_iter->hasNext())
			{
				City* city = possible_attack_iter->next();
				pq_attack.pqInsert(city);
			}
			delete possible_attack_iter;

			if (!pq_attack.pqIsEmpty())
			{
				City* best_city = pq_attack.pqRemove();
				uint8 city_id = best_city->getCityID();
				action_params[2] = city_id;
					
				action_found = true;
		 
				std::cout << "attack: " << (int) action_params[2] << std::endl;
				std::cout << "building: " << (int) action_params[1] << std::endl;
				std::cout << std::endl;
			}
		}
	}
	
	return action_found;
}

bool BasicEndeavorAI::considerPayment(uint8* action_params, bool enough_workers, bool can_use_token, CSC1310::ListArray<Building>* activated_buildings, CompareBuildingsForPayment* building_payment_comp, uint8* unactivated_building_ids, uint8 num_unactivated_buildings)
{
		bool action_found = false;
	if (enough_workers|| can_use_token)
	{
		bool building_found = false;
		if (enough_workers)
	  {
		for (int i = 0; i < num_unactivated_buildings; i++)  //13, 14, 15
		{
			if (unactivated_building_ids[i] == 13 || unactivated_building_ids[i] == 14 || unactivated_building_ids[i] == 15)
			{
				//found a building which can be used for a payment action
				action_params[0] = (int) PAYMENT_ACTION;  //payment!
				action_params[1] = unactivated_building_ids[i];
				building_found = true;
				break;
			}
		}
	  }
		
		if(can_use_token && !building_found)
		{
			action_params[0] = (int) PAYMENT_TOKEN_ACTION;
			action_params[1] = (int) PAYMENT_TOKEN;
			building_found = true;
		}

		if (building_found)
		{
			PQHeapComparator<Building> pq_payment(building_payment_comp);

			CSC1310::ListArrayIterator<Building>* possible_payment_iter = activated_buildings->iterator();
			while(possible_payment_iter->hasNext())
			{
				Building* building = possible_payment_iter->next();
				pq_payment.pqInsert(building);
			}
			delete possible_payment_iter;

			if (!pq_payment.pqIsEmpty())
			{
				Building* best_building = pq_payment.pqRemove();
				uint8 building_id = best_building->getBuildingID();
				//if (building_id >= 13) continue;
						
				action_params[2] = building_id;
				action_found = true;
			}
		}
	}
	
	return action_found;
}

uint8* BasicEndeavorAI::selectAction(uint8 player_id)
{
	CSC1310::ListArray<City> possible_cities;
	endeavor_game->getPossibleCitiesToOccupy(&possible_cities, player_id);
	CSC1310::ListArray<Ship> possible_shipping;
	endeavor_game->getNextShippingToOccupy(&possible_shipping, player_id);
	CSC1310::ListArray<Card> possible_draw;
	endeavor_game->getPossibleCardsToDraw(&possible_draw, player_id);
	CSC1310::ListArray<Building> activated_buildings;
	endeavor_game->getActivatedBuildings(&activated_buildings, player_id);
	CSC1310::ListArray<City> possible_attack;
	endeavor_game->getPossibleCitiesToAttack(&possible_attack, player_id);
   
	CompareCitiesByToken city_comp(endeavor_game, player_id, city_token_priority);
	CompareShippingByToken ship_comp(endeavor_game, ship_token_priority);
	CompareCardsByLevel card_comp(false);  //desc order
	CompareBuildingsForPayment building_payment_comp(building_payment_priority);
	
	uint8* action_params = new uint8[3];
	action_params[0] = (int) PASS_ACTION;  //pass
	
	uint8 num_ship_draw_tokens = endeavor_game->getNumActionTokens(player_id, SHIP_OR_DRAW_TOKEN);
	uint8 num_occupy_draw_tokens = endeavor_game->getNumActionTokens(player_id, OCCUPY_OR_DRAW_TOKEN);
	uint8 num_attack_tokens = endeavor_game->getNumActionTokens(player_id, ATTACK_TOKEN);
	uint8 num_payment_tokens = endeavor_game->getNumActionTokens(player_id, PAYMENT_TOKEN);
	
	std::cout << "player_id: " << (int) player_id << std::endl;

   uint8 num_unactivated_buildings = endeavor_game->getNumUnactivatedBuildings(player_id);
   uint8* unactivated_building_ids = endeavor_game->getUnactivatedBuildings(player_id);
   uint8 num_workers = endeavor_game->getNumWorkers(player_id);
   uint8 finance_level = endeavor_game->getFinanceLevel(player_id);
   
   bool enough_workers_to_occupy_with_building = (num_workers >= 2);
   bool enough_workers_to_occupy_with_token = (num_workers >= 1);
   bool can_use_occupy_draw_token = enough_workers_to_occupy_with_token && num_occupy_draw_tokens > 0;
   
   bool enough_workers_to_ship_with_building = (num_workers >= 2);
   bool enough_workers_to_ship_with_token = (num_workers >= 1);
   bool can_use_ship_draw_token_to_ship = enough_workers_to_ship_with_token && num_ship_draw_tokens > 0;
   
   bool enough_workers_to_draw_with_building = (num_workers >= 1);
   bool enough_workers_to_draw_with_token = (num_workers >= 0);
   bool can_use_ship_draw_token_to_draw = enough_workers_to_draw_with_token && num_ship_draw_tokens > 0;
   bool can_use_occupy_draw_token_to_draw = enough_workers_to_draw_with_token && num_occupy_draw_tokens > 1;
   
   bool enough_workers_to_attack_with_building = (num_workers >= 3);
   bool enough_workers_to_attack_with_token = (num_workers >= 2);
   bool can_use_attack_token = enough_workers_to_attack_with_token && num_attack_tokens > 0;
   
   bool enough_workers_to_make_payment = (num_workers >= 1);
   bool enough_workers_to_make_payment_with_token = (num_workers >= 0);
   bool can_use_payment_token = enough_workers_to_make_payment_with_token && num_payment_tokens > 0;
   
   bool action_found = false;
   
   for (int i = 0; i < 5; i++)
   {
	   if (action_found) break;
	   EndeavorActionType possible_action = action_priority[i];
	   
	   if (possible_action == OCCUPY_ACTION)
	   {
		   action_found = considerOccupy(action_params, enough_workers_to_occupy_with_building, can_use_occupy_draw_token, &possible_cities, &city_comp, unactivated_building_ids, num_unactivated_buildings);
	   }
	   
	   else if (possible_action == SHIP_ACTION)
	   {
		   action_found = considerShip(action_params, enough_workers_to_ship_with_building, can_use_ship_draw_token_to_ship, &possible_shipping, &ship_comp, unactivated_building_ids, num_unactivated_buildings);
	   }
	   
	   else if (possible_action == DRAW_ACTION)
	   {
		   action_found = considerDraw(action_params, player_id, enough_workers_to_draw_with_building, can_use_ship_draw_token_to_draw, can_use_occupy_draw_token_to_draw, &possible_draw, &card_comp, unactivated_building_ids, num_unactivated_buildings);
	   }
	   
	   else if (possible_action == ATTACK_ACTION)
	   {
		   action_found = considerAttack(action_params, enough_workers_to_attack_with_building, can_use_attack_token, &possible_attack, &city_comp, unactivated_building_ids, num_unactivated_buildings);
	   }
	   
	   else if (possible_action == PAYMENT_ACTION)
	   {
		   action_found = considerPayment(action_params, enough_workers_to_make_payment, can_use_payment_token, &activated_buildings, &building_payment_comp, unactivated_building_ids, num_unactivated_buildings);
	   }
   }

	if (!action_found)
	{
		action_params[0] = (int) PASS_ACTION;
	}
	
	delete[] unactivated_building_ids;
	return action_params;
}

uint8 BasicEndeavorAI::selectBuilding(uint8 player_id)
{
   uint8 industry_level = endeavor_game->getIndustryLevel(player_id);
   uint8 finance_level = endeavor_game->getFinanceLevel(player_id);
   uint8* available_buildings = endeavor_game->getAvailableBuildings(industry_level);

	//need to add code so that if NO buildings are available the players industry level
	//the player can select from one industry level higher
	//if there are still NO buildings, this process continues
   bool no_buildings = true;
   while(no_buildings)
   {
	   for (int i = 0; i < 15; i++)
		{
			if (available_buildings[i] > 0)
			{
				no_buildings = false;
				break;
			}
		}
		
		if (no_buildings)
		{
			delete[] available_buildings;
			industry_level++;
			available_buildings = endeavor_game->getAvailableBuildings(industry_level);
		}
   }
   
   //eventually, use frequency array of possible buildings to decide on which building to take
   bool has_level_five = endeavor_game->hasLevelFiveBuilding(player_id);

   for (int i = 0; i < 15; i++)
   {
	   EndeavorBuildingType build_select = building_select_priority[i];

	   int build_select_index = (int) build_select;
	   if (available_buildings[build_select_index - 1] > 0)
	   {
		   if (build_select == PARLIAMENT || build_select == EXCHANGE || build_select == MUSEUM)
		   {
			   if (!has_level_five)
			   {
				   delete[] available_buildings;
					return build_select_index;
			   }
		   }
	   
		   else if (build_select == BANK && finance_level < 3)
		   {
			   delete[] available_buildings;
			   return build_select_index;
		   }
	   
		   delete[] available_buildings;
		   return build_select_index;
	   }
   }
}

/*
uint8 BasicEndeavorAI::discard(uint8 player_id)
{
   //this method will only be called if the ai needs to discard
   //return the index of the card to discard
   //player card manager tries to put the weakest card at the end of the array list
cout << "discard" << endl;
   int num_cards_on_player_board = endeavor_game->getNumCardsOnPlayerBoard(player_id);
cout << num_cards_on_player_board << endl;
   return num_cards_on_player_board;  //discard the last card on the player's board
}
*/
