#include "Mediterranean.h"

#include "ListArrayIterator.h"

#include <sstream>

void Mediterranean::getPossibleCardsToDraw(CSC1310::ListArray<Card>* cards_to_draw, uint8 player_id)
{
   bool can_draw = canDrawFromRegion(player_id);
   if (!can_draw) return; 
   
   bool can_take_medit_card = canTakeSelectedCard(player_id, false);
   if (can_take_medit_card)
   {
	   cards_to_draw->add(medit_cards->lookAtTopCard());
   }
   
   bool can_take_slavery_card = canTakeSelectedCard(player_id, true);
   if (can_take_slavery_card)
   {
	   cards_to_draw->add(slavery_cards->lookAtTopCard());
   }
}

void Mediterranean::getPossibleCitiesToOccupy(CSC1310::ListArray<City>* possible_cities, uint8 player_id)
{
	if (!canOccupyInRegion()) return;
	cities->getPossibleCitiesToOccupy(possible_cities, player_id);
}

void Mediterranean::getPossibleCitiesToAttack(CSC1310::ListArray<City>* possible_cities, uint8 player_id)
{
	if (!canAttackInRegion(player_id)) return;
	cities->getPossibleCitiesToAttack(possible_cities, player_id);
}

uint8 Mediterranean::computeCityGlory(uint8 player_id)
{
   return cities->computeCityGlory(player_id);
}

bool Mediterranean::isCityInRegion(uint8 city_id)
{
	return cities->isCityInRegion(city_id);
}

bool Mediterranean::canAttackCity(uint8 player_id, uint8 city_id)
{
	return cities->canAttackCity(player_id, city_id);
}

bool Mediterranean::canAttackInRegion(uint8 player_id)
{
	return cities->canAttackInRegion(player_id);
}

bool Mediterranean::attackCity(uint8 player_id, wxBitmap* p_img, uint8 city_id)
{
	cities->attackCity(player_id, p_img, city_id);
}

bool Mediterranean::canDrawFromRegion(uint8 player_id)
{
	uint8 presence = getPlayerPresence(player_id);
	
	uint8 medit_card_level = medit_cards->getCardLevel();
	uint8 slavery_card_level = slavery_cards->getCardLevel();
	
	uint8 card_level = medit_card_level;
	if (slavery_card_level < card_level) card_level = slavery_card_level;
	return (presence >= card_level);
}

EndeavorTokenType Mediterranean::occupyCity(uint8 player_id, wxBitmap* player_img, uint8 city_id)
{
	cities->occupyCity(player_id, player_img, city_id);
}

bool Mediterranean::canOccupyCity(uint8 city_id)
{
	return cities->canOccupyCity(city_id);
}

bool Mediterranean::canOccupyInRegion()
{
	return cities->canOccupyInRegion();
}

uint8 Mediterranean::getPlayerPresence(uint8 player_id)
{
	return cities->getPlayerPresence(player_id);
}

uint8 Mediterranean::getPlayerIDInCity(uint8 city_id)
{
	return cities->getPlayerIDInCity(city_id);
}

uint8 Mediterranean::countPlayerCities(uint8 player_id)
{
   return getPlayerPresence(player_id);
}

void Mediterranean::abolishSlavery()
{
   //empty the slavery priority queue
   Card* card = slavery_cards->takeSelectedCard(0);
   while (card != NULL)
   {
	   card = slavery_cards->takeSelectedCard(0);
   }
}

void Mediterranean::returnCardToRegion(Card* card)
{
	if (card->getCardID() != SLAVERY)
	{
		medit_cards->returnCardToRegion(card);
	}
}

//depends on whether the first card was a regular card or a slavery card
/*
bool Mediterranean::canDrawSecondCard(uint8 player_id, bool is_slavery)
{
   uint8 presence = getPlayerPresence(player_id);
   uint8 card_level = 255;
   uint8 num_regular_cards = cards->size();
   uint8 num_slavery_cards = slavery->size();

   if (!is_slavery)
   {
      if (num_regular_cards > 0)
      {
         card_level = cards->peek()->getCardLevel();
      }
   }
   else
   {
      if (num_slavery_cards > 0)
      {
         card_level = slavery->peek()->getCardLevel();
      }
   }
      
   return (presence >= card_level);
}
*/

bool Mediterranean::canTakeSelectedCard(uint8 player_id, bool is_slavery)
{
	uint8 presence = getPlayerPresence(player_id);
	if (!is_slavery)
	{
		uint8 card_level = medit_cards->getCardLevel();
		return (presence >= card_level);
	}
	else
	{
		uint8 card_level = slavery_cards->getCardLevel();
		return (presence >= card_level);
	}
}

Card* Mediterranean::takeSelectedCard(uint8 player_id, bool is_slavery)
{
   
   if (!is_slavery)
	{
		return medit_cards->takeSelectedCard(player_id);
	}
	
	else
	{
		return slavery_cards->takeSelectedCard(player_id);
	}
}

EndeavorRegionType Mediterranean::findSelectedCard(uint32 x, uint32 y)
{
	EndeavorRegionType region_type_1 = medit_cards->findSelectedCard(x, y);
	EndeavorRegionType region_type_2 = slavery_cards->findSelectedCard(x, y);

	if (region_type_1 == MEDITERRANEAN)
	{
		return region_type_1;
	}
	else if (region_type_2 == SLAVERY)
	{
		return region_type_2;
	}
	
	return INVALID_REGION_TYPE;
}

uint8 Mediterranean::findSelectedCity(uint32 x, uint32 y)
{
	return cities->findSelectedCity(x, y);
}

void Mediterranean::draw(wxDC&  dc)
{
	cities->draw(dc);
   
   medit_cards->draw(dc);
   slavery_cards->draw(dc);
}

Mediterranean::Mediterranean(uint8 r_id, PixelXML& pixel_xml, ImageLoader* image_loader, CSC1310::ListArray<Token>* tokens, CSC1310::Permutation& permute, uint8 city_counter)
{

	PixelDimension pixel_card_dim = pixel_xml.getPixelDimension("mediterranean_cards");
	PixelDimension pixel_city_dim = pixel_xml.getPixelDimension("mediterranean_cities");
 
	CSC1310::ListArray<PixelPoint>* mediterranean_card_centers = pixel_xml.getPixelCentersList("mediterranean_cards");
	CSC1310::ListArray<PixelPoint>* mediterranean_city_centers = pixel_xml.getPixelCentersList("mediterranean_cities");
	
	region_id = r_id;
	//first_city_id = city_counter;
	//num_cities_in_region = mediterranean_city_centers->size();
	
	CSC1310::ListArrayIterator<PixelPoint>* mediterranean_cards_iter = mediterranean_card_centers->iterator();
	PixelPoint* card_medit_loc = mediterranean_cards_iter->next();
	PixelPoint* card_slavery_loc = mediterranean_cards_iter->next();
	delete mediterranean_cards_iter;
	delete mediterranean_card_centers;
	
	medit_cards = new Cards(MEDITERRANEAN, image_loader, *card_medit_loc, pixel_card_dim, pixel_card_dim);
	slavery_cards = new Cards(SLAVERY, image_loader, *card_slavery_loc, pixel_card_dim, pixel_card_dim);
	
	delete card_medit_loc;
	delete card_slavery_loc;

	cities = new Cities(tokens, permute, mediterranean_city_centers, pixel_city_dim, 1);
}

Mediterranean::~Mediterranean()
{   
//std::cout << "Mediterranean Destructor Called." << std::endl;

	delete cities;
   delete medit_cards;
   delete slavery_cards;
}

Card* Mediterranean::getCard(uint8 card_level, bool is_slavery)
{
	if (!is_slavery)
	{
		return medit_cards->getCard(card_level);
	}
	else
	{
		return slavery_cards->getCard(card_level);
	}
}

TiXmlElement* Mediterranean::writeXML()
{
   TiXmlElement* region_element = new TiXmlElement("Region");
   
   TiXmlElement* cities_element = cities->writeXML();
   region_element->LinkEndChild(cities_element);
   
   TiXmlElement* medit_cards_element = medit_cards->writeXML();
   region_element->LinkEndChild(medit_cards_element);
   
   TiXmlElement* slavery_cards_element = slavery_cards->writeXML();
   region_element->LinkEndChild(slavery_cards_element);
   
   return region_element;
}

void Mediterranean::readXML(TiXmlElement* region_element, wxBitmap** player_images, wxBitmap** token_images)
{
	TiXmlElement* cities_element = region_element->FirstChildElement();
	cities->readXML(cities_element, player_images, token_images);
   
	TiXmlElement* medit_cards_element = cities_element->NextSiblingElement();
	medit_cards->readXML(medit_cards_element);
	
	TiXmlElement* slavery_cards_element = medit_cards_element->NextSiblingElement();
	slavery_cards->readXML(slavery_cards_element);
}

/*
void Mediterranean::getPossibleCitiesToOccupy(ListArray<City>* cities_to_occupy)
{
   CSC1310::ListArrayIterator<City>* city_iter = cities->iterator();
   while(city_iter->hasNext())
   {
      City* city = city_iter->next();
      if (!city->isOccupied())
      {
         cities_to_occupy->add(city);
      }
   }
   delete city_iter;
}

void Mediterranean::getPossibleCardToDraw(ListArray<Card>* cards_to_draw, uint8 player_id)
{
	bool can_draw = canDrawFromRegion(player_id);
	if (!can_draw) return;
	uint8 card_level = 0;
	uint8 slavery_level = 0;

	uint8 presence = getPlayerPresence(player_id);

	uint8 num_cards = cards->size();
	if (num_cards > 0)
	{
		card_level = cards->peek()->getCardLevel();
		if (presence >= card_level)
		{
			cards_to_draw->add(cards->peek());
		}
	}

	uint8 num_slavery = slavery->size();
	if (num_slavery > 0)
	{
		slavery_level = slavery->peek()->getCardLevel();
		if (presence >= slavery_level)
		{
			cards_to_draw->add(slavery->peek());
		}
	}
}
*/
