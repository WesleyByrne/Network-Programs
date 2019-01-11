#include "Player.h"
#include "EndeavorGame.h"

#include "ListArrayIterator.h"
#include "ListLinkedIterator.h"
#include "String_.h"

void Player::placeCardsOnPlayerBoard(CSC1310::ListArray<PixelPoint>* player_board_card_locs)
{
	player_card_manager->placeCardsOnPlayerBoard(getPoliticsLevel(), player_board_card_locs);
}

uint8 Player::getNumCardsOnPlayerBoard()
{
	return player_card_manager->getNumCardsOnPlayerBoard();
}

void Player::abolishSlavery(CSC1310::ListArray<PixelPoint>* player_board_card_locs)
{
	CSC1310::ListArray<Card>* slavery_discards = player_card_manager->abolishSlavery(getPoliticsLevel());
	
	CSC1310::ListArrayIterator<Card>* abolish_iter = slavery_discards->iterator();
	while(abolish_iter->hasNext())
	{
		Card* card = abolish_iter->next();
		industry -= card->getIndustry();
		culture -= card->getCulture();
		finance -= card->getFinance();
		politics -= card->getPolitics();
		glory -= card->getGlory();
		delete card;
	}
	delete abolish_iter;
	delete slavery_discards;
	
	player_card_manager->placeCardsOnPlayerBoard(getPoliticsLevel(), player_board_card_locs);
}

void Player::computeTotalGlory(uint8 board_and_connection_glory)
{
	total_glory = glory;  //cards and buildings
	total_glory += computePlayerBoardGlory();  //track locations
	total_glory += board_and_connection_glory;  //cities and connections
	
	total_glory -= player_card_manager->getNumDiscardedSlaveryCards();
	
	if (player_card_manager->isFreeGovernorSpaceUncovered(getPoliticsLevel()))
	{
		total_glory += 3;
	}
	
	total_glory += workers/3;
}

uint8 Player::computePlayerBoardGlory()
{
	uint8 player_board_glory = 0;
	
	player_board_glory += trackGlory(industry);
	player_board_glory += trackGlory(culture);
	player_board_glory += trackGlory(finance);
	player_board_glory += trackGlory(politics);
	
	return player_board_glory;
}

uint8 Player::getNumActionTokens(EndeavorBuildingType action_type)
{
	switch(action_type)
	{
		case (SHIP_OR_DRAW_TOKEN):
		{
			return ship_or_draw_tokens;
			break;
		}
		case (OCCUPY_OR_DRAW_TOKEN):
		{
			return occupy_or_draw_tokens;
			break;
		}
		case (ATTACK_TOKEN):
		{
			return attack_tokens;
			break;
		}
		case (PAYMENT_TOKEN):
		{
			return payment_tokens;
			break;
		}
	}
}

void Player::useActionToken(EndeavorBuildingType action_type)
{
	switch(action_type)
	{
		case (SHIP_OR_DRAW_TOKEN):
		{
			ship_or_draw_tokens--;
			break;
		}
		case (OCCUPY_OR_DRAW_TOKEN):
		{
			occupy_or_draw_tokens--;
			break;
		}
		case (ATTACK_TOKEN):
		{
			attack_tokens--;
			break;
		}
		case (PAYMENT_TOKEN):
		{
			payment_tokens--;
			break;
		}
	}
}

uint8 Player::getDefaultCardToDiscard()
{
	return player_card_manager->getDefaultCardToDiscard(getPoliticsLevel());
}

Card* Player::discard(uint8 card_id, CSC1310::ListArray<PixelPoint>* player_board_card_locs)
{	
	Card* card = player_card_manager->discard(card_id, getPoliticsLevel());
	industry -= card->getIndustry();
	culture -= card->getCulture();
	finance -= card->getFinance();
	politics -= card->getPolitics();
	glory -= card->getGlory();
	
	player_card_manager->placeCardsOnPlayerBoard(getPoliticsLevel(), player_board_card_locs);
	
	return card;
}

uint8 Player::findSelectedCardToDiscard(uint32 x, uint32 y)
{
	return player_card_manager->findSelectedCardToDiscard(x, y);
}

bool Player::mustDiscard()
{
	return player_card_manager->mustDiscard(getPoliticsLevel());
}

void Player::takeSelectedCard(Card* card, CSC1310::ListArray<PixelPoint>* player_board_card_locs)
{
	industry += card->getIndustry();
	culture += card->getCulture();
	finance += card->getFinance();
	politics += card->getPolitics();
	glory += card->getGlory();
   
	player_card_manager->addCard(card, getPoliticsLevel(), player_board_card_locs);
}

void Player::workerCost(uint8 cost)
{
	workers = workers - cost;
}

void Player::occupyCity(EndeavorTokenType token_type)
{
	switch(token_type)
	{
		case INDUSTRY: industry++; industry_tokens++; break;
		case CULTURE: culture++; culture_tokens++; break;
		case FINANCE: finance++; finance_tokens++; break;
		case POLITICS: politics++; politics_tokens++; break;
		
		case SHIP_DRAW: ship_or_draw_tokens++; break;
		case OCCUPY_DRAW: occupy_or_draw_tokens++; break;
		case PAYMENT: payment_tokens++; break;
		case ATTACK: attack_tokens++; break;
	}
}

bool Player::getPass()
{
	return pass;
}

void Player::setPass(bool pass_)
{
	pass = pass_;
}

uint8 Player::getNumBuildings()
{
   return buildings->size();
}

uint8* Player::getUnactivatedBuildings()
{
   int num_unactivated = getNumUnactivatedBuildings();
   uint8* unactivated_building_ids = new uint8[num_unactivated];

   int count = 0;
   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      EndeavorBuildingType building_id = building->getBuildingID();

      if (building->canActivate() && !(building->isActivated()))
      {
         unactivated_building_ids[count] = building_id;
         count++;
      }
   }
   delete building_iter;

   return unactivated_building_ids;
}

uint8 Player::getNumUnactivatedBuildings()
{
   int count = 0;
   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      if (building->canActivate() && !(building->isActivated()))
      {
         count++;
      }
   }
   delete building_iter;
   return count;
}

void Player::getActivatedBuildings(CSC1310::ListArray<Building>* activated_buildings)
{
   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      int building_id = building->getBuildingID();

      if (building->isActivated())
      {
         activated_buildings->add(building);
      }
   }
   delete building_iter;
}

uint8 Player::getNumActivatedBuildings()
{
   uint8 count = 0;
   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      if (building->isActivated())
      {
         count++;
      }
   }
   delete building_iter;
   return count;
}

uint8 Player::getIndustryLevel()
{
   return trackFunction(industry);
}

uint8 Player::getCultureLevel()
{
   return trackFunction(culture);
}

uint8 Player::getFinanceLevel()
{
   return trackFunction(finance);
}

bool Player::mustDiscardIfCardTaken(Card* card)
{
	uint8 card_politics = card->getPolitics();
	uint8 current_politics = politics;
	uint8 possible_politics = card_politics + current_politics;
	uint8 enhanced_num_regular_allowed = trackFunction(possible_politics);
	return player_card_manager->mustDiscardIfCardTaken(card, enhanced_num_regular_allowed);
}

uint8 Player::getPoliticsLevel()
{
   return trackFunction(politics);
}

bool Player::canActivateBuilding(EndeavorBuildingType building_id)
{
   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      EndeavorBuildingType b_id = building->getBuildingID();
      if (building_id == b_id && !building->isActivated())
      {
         delete building_iter;
         return true;
      }
   }
   delete building_iter;

   return false;
}

bool Player::canMakePayment(EndeavorBuildingType selected_building_type)
{
   if (selected_building_type == INVALID_BUILDING_TYPE) return false;
   if (payments == 0) return false;

   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      EndeavorBuildingType test_building_type = building->getBuildingID();
      bool is_activated = building->isActivated();

      if (selected_building_type == test_building_type && is_activated)
      {
         delete building_iter;
         return true;
      }
   }
   delete building_iter;

   return false;
}

void Player::makePayment(EndeavorBuildingType selected_building_type)
{
	CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
	while(building_iter->hasNext())
	{
		Building* building = building_iter->next();
		EndeavorBuildingType test_building_type = building->getBuildingID();
		bool is_activated = building->isActivated();

		if (test_building_type == selected_building_type && is_activated)
		{
			payments -= 1;
			workers += 1;
			building->makePayment();  //deactivates the building
			delete building_iter;
			return;
		}
	}

	delete building_iter;
}

bool Player::canMakePaymentAction(EndeavorBuildingType selected_building_type)
{
   if (selected_building_type == INVALID_BUILDING_TYPE) return false;
   if (selected_building_type >= 13) return false; //level five buildings cannot make payments on themselves

   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      EndeavorBuildingType test_building_type = building->getBuildingID();
      bool is_activated = building->isActivated();
      if (test_building_type == selected_building_type && is_activated)
      {
         delete building_iter;
         return true;
      }
   }
   delete building_iter;

   return false;
}

//not quite the same as makePayment
void Player::makePaymentAction(EndeavorBuildingType selected_building_id)
{
   //if (selected_building_id >= 13) return; //level five buildings cannot make payments on themselves

   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      EndeavorBuildingType test_building_id = building->getBuildingID();
      bool is_activated = building->isActivated();

      if (test_building_id == selected_building_id && is_activated)
      {
         workers += 1;
         building->makePayment();
         delete building_iter;
         return;
      }
   }

   delete building_iter;
}

uint8 Player::getNumPayments()
{
   return payments;
}

wxBitmap* Player::getPlayerImage()
{
   return player_circle_img;
}

uint8 Player::getNumWorkers()
{
   return workers;
}

void Player::populationGrowth()
{
   uint8 new_workers = getCultureLevel() + 1;
   workers += new_workers;
   
   payments = getFinanceLevel();
}

void Player::takeBuilding(Building* b)
{
   buildings->add(b);
   b->setPlayerImage(player_id, player_circle_img);

   industry += b->getIndustry();
   finance += b->getFinance();
   culture += b->getCulture();
   politics += b->getPolitics();
   glory += b->getGlory();
}

bool Player::hasLevelFiveBuilding()
{
   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while (building_iter->hasNext())
   {
      Building* b = building_iter->next();
      if (b->getBuildingID() >= 13)
      {
         delete building_iter;
         return true;
      }
   }

   delete building_iter;
   return false;
}

bool Player::canTakeBuilding(EndeavorBuildingType building_type, uint8 lowest_level_available)
{
   if (buildings->size() == 8) return false;

   //can only have one level 5 building
   if (building_type == EXCHANGE || building_type == MUSEUM || building_type == PARLIAMENT)
   {
      if (hasLevelFiveBuilding()) return false;
   }

   uint8 building_level = (building_type - 1)/3 + 1;
   uint8 industry_capability = trackFunction(industry);

   if (industry_capability >= building_level || building_level == lowest_level_available)
   {
      return true;
   }
      
   return false;
}

bool Player::isPlayerSelected()
{
   return is_selected;
}

void Player::selectPlayer(bool select)
{
   is_selected = select;
}

EndeavorBuildingType Player::findSelectedBuilding(uint32 x, uint32 y)
{
   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while (building_iter->hasNext())
   {
      Building* b = building_iter->next();
      if (b->isSelectedActionCircle(x, y))
      {
         delete building_iter;
         return b->getBuildingID();
      }
   }

   delete building_iter;
   return INVALID_BUILDING_TYPE;
}

//this method will be successful if the above method is called first
void Player::activateBuilding(EndeavorBuildingType b_id)
{

   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while (building_iter->hasNext())
   {
      Building* building = building_iter->next();
      EndeavorBuildingType building_id = building->getBuildingID();

      if (b_id == building_id && !building->isActivated())
      {
         building->activate();
         workers = workers - 1;
         delete building_iter;
         return;
      }
   }

   delete building_iter;
}

uint8 Player::trackFunction(uint8 track_loc)
{
   uint8 track_result = 1;

   if (track_loc > 9) 
   {
      track_result = 5;
   }
   else if (track_loc > 6)
   {
      track_result = 4;
   }
   else if (track_loc > 3)
   {
      track_result = 3;
   }
   else if (track_loc > 1)
   {
      track_result = 2;
   }

   return track_result;
}

uint8 Player::trackGlory(uint8 track_loc)
{
   uint8 track_glory = 0;

   if (track_loc > 9) 
   {
      track_glory = track_loc;
   }
   else if (track_loc > 6)
   {
      track_glory = 7;
   }
   else if (track_loc > 3)
   {
      track_glory = 4;
   }
   else if (track_loc > 1)
   {
      track_glory = 2;
   }

   return track_glory;
}

Player::Player(uint8 p_id, wxBitmap* p_s_img, wxBitmap* p_c_img, PixelPoint& num_workers_loc, PixelDimension& marker_dim) : draw_info_font("Verdana", 10)
{
	player_marker_width = marker_dim.getWidth();
	player_marker_height = marker_dim.getHeight();
	num_workers_loc_x = num_workers_loc.getX();
	num_workers_loc_y = num_workers_loc.getY();
	
	player_id = p_id;
	player_square_img = p_s_img;
	player_circle_img = p_c_img;

	industry = 0;
	culture = 0;
	finance = 0;
	politics = 0;
	glory = 0;
	
	total_glory = 0;

	workers = 0;
	payments = 0;

	is_selected = false;

	buildings = new CSC1310::ListLinked<Building>();

	industry_tokens = 0;
	culture_tokens = 0;
	finance_tokens = 0;
	politics_tokens = 0;
	
	ship_or_draw_tokens = 0;
	occupy_or_draw_tokens = 0;
	payment_tokens = 0;
	attack_tokens = 0;
	
	pass = false;
	
	player_card_manager = new PlayerCardManager();
}

Player::~Player()
{
	delete player_card_manager;
	
	CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
	while(building_iter->hasNext())
	{
		Building* building = building_iter->next();
		delete building;
	}
	delete building_iter;
	delete buildings;
}

void Player::draw(wxDC&  dc, uint8 active_player, CSC1310::ListArray<PixelPoint>* track_locations, CSC1310::ListArray<PixelPoint>* info_locations)
{
	if (player_id == active_player)
	{
		int track_right_shift = 31;  //amount to move to the right for each token earned
			
		//industry_track
		PixelPoint* industry_track = track_locations->get(1);
		int industry_track_start_x = industry_track->getX();
		int industry_track_y = industry_track->getY();

		int industry_x_loc = industry_track_start_x + industry*track_right_shift;
		dc.DrawBitmap(*player_square_img, industry_x_loc, industry_track_y);

		//culture track marker
		PixelPoint* culture_track = track_locations->get(2);
		int culture_track_start_x = culture_track->getX();
		int culture_track_y = culture_track->getY();

		int culture_x_loc = culture_track_start_x + culture*track_right_shift;
		dc.DrawBitmap(*player_square_img, culture_x_loc, culture_track_y);

		//finance track marker
		PixelPoint* finance_track = track_locations->get(3);
		int finance_track_start_x = finance_track->getX();
		int finance_track_y = finance_track->getY();

		int finance_x_loc = finance_track_start_x + finance*track_right_shift;
		dc.DrawBitmap(*player_square_img, finance_x_loc, finance_track_y);

		//politics track marker
		PixelPoint* politics_track = track_locations->get(4);
		int politics_track_start_x = politics_track->getX();
		int politics_track_y = politics_track->getY();

		int politics_x_loc = politics_track_start_x + politics*track_right_shift;
		dc.DrawBitmap(*player_square_img, politics_x_loc, politics_track_y);

		CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
		while (building_iter->hasNext())
		{
			Building* building = building_iter->next();
			building->draw(dc);
		}
		delete building_iter;
	   
		dc.DrawBitmap(*player_circle_img, num_workers_loc_x, num_workers_loc_y);
	   
		PixelPoint* info_loc = info_locations->get(1);
		draw_info_font.draw(dc, CSC1310::String::i_to_a(workers).get_std_str(), info_loc->getX(), info_loc->getY());

		info_loc = info_locations->get(5);
		draw_info_font.draw(dc, CSC1310::String::i_to_a(industry_tokens).get_std_str(), info_loc->getX(), info_loc->getY());
		
		info_loc = info_locations->get(2);
		draw_info_font.draw(dc, CSC1310::String::i_to_a(culture_tokens).get_std_str(), info_loc->getX(), info_loc->getY());
		
		info_loc = info_locations->get(4);
		draw_info_font.draw(dc, CSC1310::String::i_to_a(finance_tokens).get_std_str(), info_loc->getX(), info_loc->getY());
		
		info_loc = info_locations->get(3);
		draw_info_font.draw(dc, CSC1310::String::i_to_a(politics_tokens).get_std_str(), info_loc->getX(), info_loc->getY());
		
		info_loc = info_locations->get(6);
		draw_info_font.draw(dc, CSC1310::String::i_to_a(total_glory).get_std_str(), info_loc->getX(), info_loc->getY());
		
		info_loc = info_locations->get(7);
		draw_info_font.draw(dc, CSC1310::String::i_to_a(ship_or_draw_tokens).get_std_str(), info_loc->getX(), info_loc->getY());

		info_loc = info_locations->get(8);
		draw_info_font.draw(dc, CSC1310::String::i_to_a(occupy_or_draw_tokens).get_std_str(), info_loc->getX(), info_loc->getY());
		
		info_loc = info_locations->get(9);
		draw_info_font.draw(dc, CSC1310::String::i_to_a(payment_tokens).get_std_str(), info_loc->getX(), info_loc->getY());
		
		info_loc = info_locations->get(10);
		draw_info_font.draw(dc, CSC1310::String::i_to_a(attack_tokens).get_std_str(), info_loc->getX(), info_loc->getY());
		
		player_card_manager->draw(dc);
	}
}
	
TiXmlElement* Player::writeXML()
{
	TiXmlElement* player_element = new TiXmlElement("Player");
	
	TiXmlElement* player_id_element = EndeavorGame::xmlElementFromInteger("player_id", (int) player_id);
	player_element->LinkEndChild(player_id_element);
	
	TiXmlElement* workers_element = EndeavorGame::xmlElementFromInteger("workers", (int) workers);
	player_element->LinkEndChild(workers_element);
	
	TiXmlElement* payments_element = EndeavorGame::xmlElementFromInteger("payments", (int) payments);
	player_element->LinkEndChild(payments_element);
	
	TiXmlElement* industry_element = EndeavorGame::xmlElementFromInteger("industry", (int) industry);
	player_element->LinkEndChild(industry_element);
	
	TiXmlElement* culture_element = EndeavorGame::xmlElementFromInteger("culture", (int) culture);
	player_element->LinkEndChild(culture_element);
	
	TiXmlElement* finance_element = EndeavorGame::xmlElementFromInteger("finance", (int) finance);
	player_element->LinkEndChild(finance_element);
	
	TiXmlElement* politics_element = EndeavorGame::xmlElementFromInteger("politics", (int) politics);
	player_element->LinkEndChild(politics_element);
	
	TiXmlElement* industry_tokens_element = EndeavorGame::xmlElementFromInteger("industry_tokens", (int) industry_tokens);
	player_element->LinkEndChild(industry_tokens_element);
	
	TiXmlElement* culture_tokens_element = EndeavorGame::xmlElementFromInteger("culture_tokens", (int) culture_tokens);
	player_element->LinkEndChild(culture_tokens_element);
	
	TiXmlElement* finance_tokens_element = EndeavorGame::xmlElementFromInteger("finance_tokens", (int) finance_tokens);
	player_element->LinkEndChild(finance_tokens_element);
	
	TiXmlElement* politics_tokens_element = EndeavorGame::xmlElementFromInteger("politics_tokens", (int) politics_tokens);
	player_element->LinkEndChild(politics_tokens_element);
	
	TiXmlElement* ship_or_draw_tokens_element = EndeavorGame::xmlElementFromInteger("ship_or_draw_tokens", (int) ship_or_draw_tokens);
	player_element->LinkEndChild(ship_or_draw_tokens_element);
	
	TiXmlElement* occupy_or_draw_tokens_element = EndeavorGame::xmlElementFromInteger("occupy_or_draw_tokens", (int) occupy_or_draw_tokens);
	player_element->LinkEndChild(occupy_or_draw_tokens_element);
	
	TiXmlElement* attack_tokens_element = EndeavorGame::xmlElementFromInteger("attack_tokens", (int) attack_tokens);
	player_element->LinkEndChild(attack_tokens_element);
	
	TiXmlElement* payment_tokens_element = EndeavorGame::xmlElementFromInteger("payment_tokens", (int) payment_tokens);
	player_element->LinkEndChild(payment_tokens_element);
	
	TiXmlElement* pass_element = EndeavorGame::xmlElementFromInteger("pass", (int) pass);
	player_element->LinkEndChild(pass_element);
	
	TiXmlElement* is_selected_element = EndeavorGame::xmlElementFromInteger("is_selected", (int) is_selected);
	player_element->LinkEndChild(is_selected_element);
	
	TiXmlElement* glory_element = EndeavorGame::xmlElementFromInteger("glory", (int) glory);
	player_element->LinkEndChild(glory_element);
	
	TiXmlElement* total_glory_element = EndeavorGame::xmlElementFromInteger("total_glory", (int) total_glory);
	player_element->LinkEndChild(total_glory_element);
	
	TiXmlElement* player_cards = player_card_manager->writeXML();
	player_element->LinkEndChild(player_cards);
	
	TiXmlElement* buildings_element = new TiXmlElement("Buildings");
   
   CSC1310::ListLinkedIterator<Building>* buildings_iter = buildings->iterator();
	while(buildings_iter->hasNext())
	{
		Building* building = buildings_iter->next();
		TiXmlElement* building_element = building->writeXML();
		buildings_element->LinkEndChild(building_element);
	}
	delete buildings_iter;
	player_element->LinkEndChild(buildings_element);
	
	return player_element;
}

void Player::readXML(TiXmlElement* player_element, EndeavorGame* game, CSC1310::ListArray<PixelPoint>* player_board_card_locs, CSC1310::ListArray<PixelPoint>* player_building_locations)
{	  
/*
	TiXmlElement* scheme_element = gui_element->FirstChildElement("scheme");
	std::string scheme_element_str = scheme_element->GetText();
   */
	TiXmlElement* player_id_element = player_element->FirstChildElement("player_id");
	player_id = (uint8) EndeavorGame::integerFromXMLElement(player_id_element);
	
	TiXmlElement* workers_element = player_element->FirstChildElement("workers");
	workers = (uint8) EndeavorGame::integerFromXMLElement(workers_element);

	TiXmlElement* payments_element = player_element->FirstChildElement("payments");
	payments = (uint8) EndeavorGame::integerFromXMLElement(payments_element);
	
	TiXmlElement* industry_element = player_element->FirstChildElement("industry");
	industry = (uint8) EndeavorGame::integerFromXMLElement(industry_element);
	
	TiXmlElement* culture_element = player_element->FirstChildElement("culture");
	culture = (uint8) EndeavorGame::integerFromXMLElement(culture_element);
	
	TiXmlElement* finance_element = player_element->FirstChildElement("finance");
	finance = (uint8) EndeavorGame::integerFromXMLElement(finance_element);
	
	TiXmlElement* politics_element = player_element->FirstChildElement("politics");
	politics = (uint8) EndeavorGame::integerFromXMLElement(politics_element);
	
	TiXmlElement* industry_tokens_element = player_element->FirstChildElement("industry_tokens");
	industry_tokens = (uint8) EndeavorGame::integerFromXMLElement(industry_tokens_element);
	
	TiXmlElement* culture_tokens_element = player_element->FirstChildElement("culture_tokens");
	culture_tokens = (uint8) EndeavorGame::integerFromXMLElement(culture_tokens_element);
	
	TiXmlElement* finance_tokens_element = player_element->FirstChildElement("finance_tokens");
	finance_tokens = (uint8) EndeavorGame::integerFromXMLElement(finance_tokens_element);
	
	TiXmlElement* politics_tokens_element = player_element->FirstChildElement("politics_tokens");
	politics_tokens = (uint8) EndeavorGame::integerFromXMLElement(politics_tokens_element);
	
	TiXmlElement* ship_or_draw_tokens_element = player_element->FirstChildElement("ship_or_draw_tokens");
	ship_or_draw_tokens = (uint8) EndeavorGame::integerFromXMLElement(ship_or_draw_tokens_element);
	
	TiXmlElement* occupy_or_draw_tokens_element = player_element->FirstChildElement("occupy_or_draw_tokens");
	occupy_or_draw_tokens = (uint8) EndeavorGame::integerFromXMLElement(occupy_or_draw_tokens_element);
	
	TiXmlElement* attack_tokens_element = player_element->FirstChildElement("attack_tokens");
	attack_tokens = (uint8) EndeavorGame::integerFromXMLElement(attack_tokens_element);
	
	TiXmlElement* payment_tokens_element = player_element->FirstChildElement("payment_tokens");
	payment_tokens = (uint8) EndeavorGame::integerFromXMLElement(payment_tokens_element);
	
	TiXmlElement* pass_element = player_element->FirstChildElement("pass");
	pass = (bool) EndeavorGame::integerFromXMLElement(pass_element);
	
	TiXmlElement* is_selected_element = player_element->FirstChildElement("is_selected");
	is_selected = (bool) EndeavorGame::integerFromXMLElement(is_selected_element);
	
	TiXmlElement* glory_element = player_element->FirstChildElement("glory");
	glory = (uint8) EndeavorGame::integerFromXMLElement(glory_element);
	
	TiXmlElement* total_glory_element = player_element->FirstChildElement("total_glory");
	total_glory = (uint8) EndeavorGame::integerFromXMLElement(total_glory_element);

   TiXmlElement* player_cards_element = player_element->FirstChildElement("Cards");
   player_card_manager->readXML(player_cards_element, game, getPoliticsLevel(), player_board_card_locs);
   
   buildings->removeAll();
	
   TiXmlElement* buildings_element = player_cards_element->NextSiblingElement();
   TiXmlElement* building_element = buildings_element->FirstChildElement();
   int building_count = 1;
   while(building_element != NULL)
   {
	   TiXmlElement* building_unique_id_element = building_element->FirstChildElement();
	   uint8 unique_id = (uint8) EndeavorGame::integerFromXMLElement(building_unique_id_element);

	   Building* building = game->getSpecificBuilding(unique_id);
	   building->readXML(building_element);
	   building->setPlayerImage(player_id, player_circle_img);
	   building->setBuildingLocation(*player_building_locations->get(building_count));
	   buildings->add(building);
	   building_element = building_element->NextSiblingElement();
	   building_count++;
   }
}
