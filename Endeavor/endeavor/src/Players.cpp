#include "Players.h"
#include "EndeavorGame.h"

#include "ListArrayIterator.h"

#include "Random.h"

void Players::placeCardsOnPlayerBoard()
{
	for (int i = 1; i <= 5; i++)
	{
		Player* p = players->get(i);
	    p->placeCardsOnPlayerBoard(player_card_locations);
	}
}

uint8 Players::getNumCardsOnPlayerBoard(uint8 player_id)
{
	Player* p = players->get(player_id);
	return p->getNumCardsOnPlayerBoard();
}

uint8 Players::getNumActionTokens(uint8 player_id, EndeavorBuildingType action_type)
{
	Player* p = players->get(player_id);
	return p->getNumActionTokens(action_type);
}

void Players::useActionToken(uint8 player_id, EndeavorBuildingType action_type)
{
	Player* p = players->get(player_id);
	p->useActionToken(action_type);
}

bool Players::mustDiscardIfCardTaken(Card* card, uint8 player_id)
{
	Player* p = players->get(player_id);
	return p->mustDiscardIfCardTaken(card);
}

void Players::abolishSlavery()
{
	CSC1310::ListArrayIterator<Player>* player_iter = players->iterator();
	while(player_iter->hasNext())
	{
		Player* player = player_iter->next();
		player->abolishSlavery(player_card_locations);
	}
	delete player_iter;
}

void Players::computeTotalGlory(uint8 player_id, uint8 board_and_connection_glory)
{
	Player* p = players->get(player_id);
	p->computeTotalGlory(board_and_connection_glory);
}

uint8 Players::getDefaultCardToDiscard(uint8 player_id)
{
	Player* p = players->get(player_id);
	return p->getDefaultCardToDiscard();
}

Card* Players::discard(uint8 player_id, uint8 card_id)
{
	Player* p = players->get(player_id);
	return p->discard(card_id, player_card_locations);
}

uint8 Players::findSelectedCardToDiscard(uint8 player_id, uint32 x, uint32 y)
{
	Player* p = players->get(player_id);
	return p->findSelectedCardToDiscard(x, y);
}

bool Players::mustDiscard(uint8 player_id)
{
	Player* p = players->get(player_id);
	return p->mustDiscard();
}

void Players::ship(uint8 player_id, EndeavorTokenType token_type)
{
	Player* p = players->get(player_id);
	p->occupyCity(token_type);
	p->workerCost(1);
}

void Players::takeSelectedCard(uint8 player_id, Card* card)
{
	card->setPlayerID(player_id);  //so that PlayerCardManager can extract the player id
	Player* p = players->get(player_id);
	p->takeSelectedCard(card, player_card_locations);
}

void Players::occupyCity(uint8 player_id, CSC1310::ListArray<CSC1310::Integer>* token_types, uint8 worker_cost)
{
	Player* p = players->get(player_id);
	CSC1310::ListArrayIterator<CSC1310::Integer>* token_types_iter = token_types->iterator();
	while(token_types_iter->hasNext())
	{
		CSC1310::Integer* token_type = token_types_iter->next();
		p->occupyCity((EndeavorTokenType) token_type->getValue());
		delete token_type;
	}
	delete token_types_iter;
	delete token_types;
	
	p->workerCost(worker_cost);
	view_player = active_player;
}

EndeavorBuildingType Players::findSelectedBuilding(uint8 player_id, uint32 x, uint32 y)
{
	Player* p = players->get(player_id);
	EndeavorBuildingType building_type = p->findSelectedBuilding(x, y);
	if (building_type == INVALID_BUILDING_TYPE)
	{
		building_type = findSelectedActionToken(player_id, x, y);
	}
	return building_type;
}

EndeavorBuildingType Players::findSelectedActionToken(uint8 player_id, uint32 x, uint32 y)
{
   EndeavorBuildingType  action_token_type = SHIP_OR_DRAW_TOKEN;

   CSC1310::ListArrayIterator<HotSpot>* action_token_iter = action_token_hot_spots->iterator();
   while(action_token_iter->hasNext())
   {
      HotSpot* hot_spot = action_token_iter->next();
      if (hot_spot->isSelectedHotSpot(x, y))
      {
		 Player* p = players->get(player_id);
		 if (p->getNumActionTokens(action_token_type) > 0)
		 {
			 delete action_token_iter;
			return action_token_type;
		 }
      }
      action_token_type = (EndeavorBuildingType) ((int)action_token_type + 1);
   }
   delete action_token_iter;
   return INVALID_BUILDING_TYPE;  
}

uint8 Players::getNumWorkers(uint8 player_id)
{
	Player* p = players->get(player_id);
	return p->getNumWorkers();
}

void Players::populationGrowth(uint8 player_id)
{
	Player* p = players->get(player_id);
	p->populationGrowth();
}

uint8 Players::getGameRound()
{
	return game_round;
}

//should only be called from ActionState (perhaps DiscardState later)
bool Players::nextPlayerAfterPassCheckForNewRound()
{
	bool next_round = nextPlayerAfterPass();
	if (next_round)
	{
		start_player++;
		if (start_player == 6)
		{
			start_player = 1;
		}
		active_player = start_player;
		view_player = active_player;
		game_round++;
	}
	
	return next_round;
}

bool Players::nextPlayerAfterPass()
{
	bool next_phase = false;
	
	Player* current_player = players->get(active_player);
	current_player->setPass(true);
	player_pass_count++;

	if (player_pass_count == 5)
	{
		player_pass_count = 0;
		next_phase = true;
		
		for (int i = 1; i <= 5; i++)
		{
			Player* p = players->get(i);
			p->setPass(false);
		}
	}

	nextPlayer();
	return next_phase;
}

void Players::nextPlayer()
{
	active_player++;
	if (active_player == 6) {active_player = 1;}
	Player* current_player = players->get(active_player);
	//look for a player that has not yet passed
	while(current_player->getPass())
	{
		active_player++;
		if (active_player == 6) {active_player = 1;}
		current_player = players->get(active_player);
	}
	view_player = active_player;
}

bool Players::doesPlayerPass(uint32 x, uint32 y)
{
	return player_pass_hot_spot->isSelectedHotSpot(x, y);
}

void Players::selectPlayer(uint8 player_id)
{
	view_player = player_id;
}

uint8 Players::getViewPlayer()
{
	return view_player;
}

uint8 Players::findSelectedPlayer(uint32 x, uint32 y)
{
   int view_count = 1;

   CSC1310::ListArrayIterator<HotSpot>* player_iter = player_view_hot_spots->iterator();
   while(player_iter->hasNext())
   {
      HotSpot* hot_spot = player_iter->next();
      if (hot_spot->isSelectedHotSpot(x, y))
      {
         delete player_iter;
         return view_count;
      }
      view_count++;
   }
   delete player_iter;
   return 0;  
}

bool Players::hasLevelFiveBuilding(uint8 player_id)
{
   Player* p = players->get(player_id);
   return p->hasLevelFiveBuilding();
}

uint8 Players::getNumUnactivatedBuildings(uint8 player_id)
{
   Player* p = players->get(player_id);
   return p->getNumUnactivatedBuildings();
}

uint8* Players::getUnactivatedBuildings(uint8 player_id)
{
   Player* p = players->get(player_id);
   return p->getUnactivatedBuildings();
}

uint8 Players::getNumActivatedBuildings(uint8 player_id)
{
   Player* p = players->get(player_id);
   return p->getNumActivatedBuildings();
}

void Players::getActivatedBuildings(CSC1310::ListArray<Building>* activated_buildings, uint8 player_id)
{
   Player* p = players->get(player_id);
   p->getActivatedBuildings(activated_buildings);
}

uint8 Players::getIndustryLevel(uint8 player_id)
{
   Player* p = players->get(player_id);
   return p->getIndustryLevel();
}

uint8 Players::getCultureLevel(uint8 player_id)
{
   Player* p = players->get(player_id);
   return p->getCultureLevel();
}

uint8 Players::getFinanceLevel(uint8 player_id)
{
   Player* p = players->get(player_id);
   return p->getFinanceLevel();
}

uint8 Players::getPoliticsLevel(uint8 player_id)
{
   Player* p = players->get(player_id);
   return p->getPoliticsLevel();
}

void Players::draw(wxDC&  dc)
{
   //draw the start player graphic
   int x_loc = 30;
   int y_loc = (start_player - 1) * 60 + 212;

   dc.DrawBitmap(*start_player_img, x_loc, y_loc);

   //draw the active player graphic
   x_loc = 29;
   y_loc = (active_player - 1) * 60 + 220;

   dc.DrawBitmap(*active_player_img, x_loc, y_loc);
   
   uint8 view_player = getViewPlayer();
   CSC1310::ListArrayIterator<Player>* player_iter = players->iterator();
   while (player_iter->hasNext())
   {
		Player* player = player_iter->next();
		player->draw(dc, view_player, player_track_locations, player_info_locations);
   }
   delete player_iter;
}

uint8 Players::getActivePlayer()
{
   return active_player;
}

uint8 Players::getStartPlayer()
{
   return start_player;
}

wxBitmap* Players::getPlayerImage(uint8 player_id)
{
   Player* p = players->get(player_id);
   return p->getPlayerImage();
}

void Players::takeBuilding(uint8 player_id, Building* b)
{
   Player* p = players->get(player_id);
   uint8 num_buildings = p->getNumBuildings();
   PixelPoint* building_location = player_building_locations->get(num_buildings + 1);
   b->setBuildingLocation(*building_location);
   p->takeBuilding(b);
}

bool Players::canTakeBuilding(uint8 player_id, EndeavorBuildingType building_id, uint8 lowest_level_available)
{
	Player* p = players->get(player_id);
	return p->canTakeBuilding(building_id, lowest_level_available);
}

void Players::activateBuilding(uint8 player_id, EndeavorBuildingType building_id)
{
	view_player = active_player;
	Player* p = players->get(player_id);
	p->activateBuilding(building_id);
}

bool Players::canMakePayment(uint8 player_id, EndeavorBuildingType building_type)
{
   Player* p = players->get(player_id);
   return p->canMakePayment(building_type);
}

void Players::makePayment(uint8 player_id, EndeavorBuildingType building_type)
{
   Player* p = players->get(player_id);
   return p->makePayment(building_type);
}

uint8 Players::getNumPayments(uint8 player_id)
{
   Player* p = players->get(player_id);
   return p->getNumPayments();
}

bool Players::canActivateBuilding(uint8 player_id, EndeavorBuildingType building_id)
{
   Player* p = players->get(player_id);
   return p->canActivateBuilding(building_id);
}

bool Players::canMakePaymentAction(uint8 player_id, EndeavorBuildingType building_id)
{
   Player* p = players->get(player_id);
   return p->canMakePaymentAction(building_id);
}

void Players::makePaymentAction(uint8 player_id, EndeavorBuildingType building_id)
{
   Player* p = players->get(player_id);
   p->makePaymentAction(building_id);
}

Players::Players(PixelXML& pixel_xml, ImageLoader* image_loader, Buildings* buildings)
{
	player_card_locations = pixel_xml.getPixelCentersList("player_card_locations");
	
	PixelPoint player_pass_loc = pixel_xml.getPixelCenter("player_pass");
	PixelDimension player_pass_dim = pixel_xml.getPixelDimension("player_pass");
	player_pass_hot_spot = new HotSpot(0, player_pass_loc, player_pass_dim);

	player_building_locations = pixel_xml.getPixelCentersList("player_building_locations");
	PixelDimension pixel_dim = pixel_xml.getPixelDimension("player_building_locations");
	
	PixelDimension marker_dim = pixel_xml.getPixelDimension("player_marker");
	PixelPoint num_workers_loc = pixel_xml.getPixelCenter("player_marker");
	player_track_locations = pixel_xml.getPixelCentersList("player_track_start_locations");

	players = new CSC1310::ListArray<Player>();

	player_square_images = new wxBitmap*[5];
	player_circle_images = new wxBitmap*[5];

   player_square_images[0] = image_loader->loadImageRGBA("red_square");
   player_circle_images[0] = image_loader->loadImageRGBA("red_circle");
   Player* p = new Player(1, player_square_images[0], player_circle_images[0], num_workers_loc, marker_dim);
   players->add(p);
   
   player_square_images[1] = image_loader->loadImageRGBA("purple_square");
   player_circle_images[1] = image_loader->loadImageRGBA("purple_circle");
   p = new Player(2, player_square_images[1], player_circle_images[1], num_workers_loc, marker_dim);
   players->add(p);

   player_square_images[2] = image_loader->loadImageRGBA("orange_square");
   player_circle_images[2] = image_loader->loadImageRGBA("orange_circle");
   p = new Player(3, player_square_images[2], player_circle_images[2], num_workers_loc, marker_dim);
   players->add(p);
   
   player_square_images[3] = image_loader->loadImageRGBA("blue_square");
   player_circle_images[3] = image_loader->loadImageRGBA("blue_circle");
   p = new Player(4, player_square_images[3], player_circle_images[3], num_workers_loc, marker_dim);
   players->add(p);

   player_square_images[4] = image_loader->loadImageRGBA("green_square");
   player_circle_images[4] = image_loader->loadImageRGBA("green_circle");
   p = new Player(5, player_square_images[4], player_circle_images[4], num_workers_loc, marker_dim);
   players->add(p);

   PixelPoint* pixel_point_colonial_house = player_building_locations->get(1);
   
	Building* colonial_house = NULL;
	for (int i = 1; i <= 5; i++)
	{
		colonial_house = buildings->removeBuilding(COLONIAL_HOUSE);
		colonial_house->setBuildingLocation(*pixel_point_colonial_house);
		players->get(i)->takeBuilding(colonial_house);
	}
	
	CSC1310::ListArray<PixelPoint>* player_view_locations = pixel_xml.getPixelCentersList("player_view_locations");
	PixelDimension pixel_view_dim = pixel_xml.getPixelDimension("player_view_locations");
	player_view_hot_spots = new CSC1310::ListArray<HotSpot>();
	for (int i = 1; i <= 5; i++)
	{
		PixelPoint* view_center = player_view_locations->get(i);
		HotSpot* hot_spot = new HotSpot(i, *view_center, pixel_view_dim);
		player_view_hot_spots->add(hot_spot);
	}
	
	CSC1310::ListArrayIterator<PixelPoint>* point_view_iter = player_view_locations->iterator();
	while(point_view_iter->hasNext())
	{
		PixelPoint* point_view = point_view_iter->next();
		delete point_view;
	}
	delete point_view_iter;
	delete player_view_locations;
	
	CSC1310::ListArray<PixelPoint>* action_token_locations = pixel_xml.getPixelCentersList("action_token_locations");
	PixelDimension action_token_dim = pixel_xml.getPixelDimension("action_token_locations");
	action_token_hot_spots = new CSC1310::ListArray<HotSpot>();
	for (int i = 1; i <= 4; i++)
	{
		PixelPoint* action_token_center = action_token_locations->get(i);
		HotSpot* hot_spot = new HotSpot(i, *action_token_center, action_token_dim);
		action_token_hot_spots->add(hot_spot);
	}
	
	CSC1310::ListArrayIterator<PixelPoint>* action_token_iter = action_token_locations->iterator();
	while(action_token_iter->hasNext())
	{
		PixelPoint* action_token_center = action_token_iter->next();
		delete action_token_center;
	}
	delete action_token_iter;
	delete action_token_locations;
	
	player_info_locations = pixel_xml.getPixelCentersList("player_info_locations");
   
   //initialize start player and active player
   CSC1310::Random* rand = CSC1310::Random::getRandom();
   start_player = rand->getRandomInt(1, 5);
   p = players->get(start_player);
   p->selectPlayer(true);
   active_player = start_player;
   view_player = active_player;
   player_pass_count = 0;

   start_player_img = image_loader->loadImageRGBA("start_player");
   active_player_img = image_loader->loadImageRGBA("active_player");
   
   game_round = 1;
}

Players::~Players()
{
	delete player_pass_hot_spot;
	
	for (int i = 0; i < 5; i++)
	{
		delete player_square_images[i];
		delete player_circle_images[i];
	}
	delete[] player_square_images;
	delete[] player_circle_images;
	
	CSC1310::ListArrayIterator<HotSpot>* action_token_hot_iter = action_token_hot_spots->iterator();
	while(action_token_hot_iter->hasNext())
	{
		HotSpot* action_token_hot = action_token_hot_iter->next();
		delete action_token_hot;
	}
	delete action_token_hot_iter;
	delete action_token_hot_spots;
	
	CSC1310::ListArrayIterator<HotSpot>* player_view_iter = player_view_hot_spots->iterator();
	while(player_view_iter->hasNext())
	{
		HotSpot* player_view_loc = player_view_iter->next();
		delete player_view_loc;
	}
	delete player_view_iter;
	delete player_view_hot_spots;
	
	//should write a method to do this!
	CSC1310::ListArrayIterator<PixelPoint>* player_card_iter = player_card_locations->iterator();
	while(player_card_iter->hasNext())
	{
		PixelPoint* player_card_loc = player_card_iter->next();
		delete player_card_loc;
	}
	delete player_card_iter;
	delete player_card_locations;
	
	CSC1310::ListArrayIterator<PixelPoint>* player_info_iter = player_info_locations->iterator();
	while(player_info_iter->hasNext())
	{
		PixelPoint* player_info_loc = player_info_iter->next();
		delete player_info_loc;
	}
	delete player_info_iter;
	delete player_info_locations;
	
	CSC1310::ListArrayIterator<PixelPoint>* track_locs_iter = player_track_locations->iterator();
	while(track_locs_iter->hasNext())
	{
		PixelPoint* track_loc = track_locs_iter->next();
		delete track_loc;
	}
	delete track_locs_iter;
	delete player_track_locations;
   
   CSC1310::ListArrayIterator<PixelPoint>* iter_building = player_building_locations->iterator();
   while(iter_building->hasNext())
   {
      PixelPoint* pixel_point = iter_building->next();
      delete pixel_point;
   }
   delete iter_building;
   delete player_building_locations;
   
   CSC1310::ListArrayIterator<Player>* iter_player = players->iterator();
   while(iter_player->hasNext())
   {
      Player* player = iter_player->next();
      delete player;
   }
   delete iter_player;
   delete players;
}

TiXmlElement* Players::writeXML()
{
	TiXmlElement* players_element = new TiXmlElement("Players");
	
	TiXmlElement* active_player_element = EndeavorGame::xmlElementFromInteger("active_player", (int) active_player);
	players_element->LinkEndChild(active_player_element);
	
	TiXmlElement* start_player_element = EndeavorGame::xmlElementFromInteger("start_player", (int) start_player);
	players_element->LinkEndChild(start_player_element);
	
	TiXmlElement* view_player_element = EndeavorGame::xmlElementFromInteger("view_player", (int) view_player);
	players_element->LinkEndChild(view_player_element);
	
	TiXmlElement* player_pass_count_element = EndeavorGame::xmlElementFromInteger("player_pass_count", (int) player_pass_count);
	players_element->LinkEndChild(player_pass_count_element);
	
	TiXmlElement* game_round_element = EndeavorGame::xmlElementFromInteger("game_round", (int) game_round);
	players_element->LinkEndChild(game_round_element);

	CSC1310::ListArrayIterator<Player>* player_iter = players->iterator();
	while(player_iter->hasNext())
	{
		Player* player = player_iter->next();
		TiXmlElement* player_element = player->writeXML();
		players_element->LinkEndChild(player_element);
	}
	delete player_iter;
	
	return players_element;
}

void Players::readXML(TiXmlElement* players_element, EndeavorGame* game)
{	  
	TiXmlElement* active_player_element = players_element->FirstChildElement("active_player");
	active_player = (uint8) EndeavorGame::integerFromXMLElement(active_player_element);
	
	TiXmlElement* start_player_element = players_element->FirstChildElement("start_player");
	start_player = (uint8) EndeavorGame::integerFromXMLElement(start_player_element);
	
	TiXmlElement* view_player_element = players_element->FirstChildElement("view_player");
	view_player = (uint8) EndeavorGame::integerFromXMLElement(view_player_element);
	
	TiXmlElement* player_pass_count_element = players_element->FirstChildElement("player_pass_count");
	player_pass_count = (uint8) EndeavorGame::integerFromXMLElement(player_pass_count_element);
	
	TiXmlElement* game_round_element = players_element->FirstChildElement("game_round");
	game_round = (uint8) EndeavorGame::integerFromXMLElement(game_round_element);

   TiXmlElement* player_element = players_element->FirstChildElement("Player");
   int count = 1;
   while(player_element != NULL)
   {
	   Player* player = players->get(count);
	   player->readXML(player_element, game, player_card_locations, player_building_locations);
	   player_element = player_element->NextSiblingElement();
	   count++;
   }
}
