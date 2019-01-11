#include "Region.h"

#include "ListArrayIterator.h"

void Region::getPossibleCardToDraw(CSC1310::ListArray<Card>* cards_to_draw, uint8 player_id)
{
   if (!open) return;  //no cards can be drawn as region is closed

   bool can_draw = canDrawFromRegion(player_id);
   if (!can_draw) return; 

   cards_to_draw->add(cards->lookAtTopCard());
}

uint8 Region::getNumOpenRegularLocations()
{
	return shipping_lane->getNumOpenRegularLocations();
}

uint8 Region::computeCityGlory(uint8 player_id)
{
	return cities->computeCityGlory(player_id);
}

EndeavorRegionType Region::getRegionWithCity(uint8 city_id)
{
	if (cities->isCityInRegion(city_id))
	{
		return region_type;
	}
	return INVALID_REGION_TYPE;
}

int Region::compareRegions(Region* region_1, Region* region_2)
{
	//the start city index is the key
	CSC1310::String* key_1 = region_1->getRegionStartKey();
	CSC1310::String* key_2 = region_2->getRegionStartKey();
	return key_1->compare(key_2);
}

int Region::compareRegionsByKeyAndRegion(CSC1310::String* key_1, Region* region)
{
	uint8 key_1_city_id = (uint8) key_1->a_to_i();
	//next line very important
	if (region->isCityInRegion(key_1_city_id)) return 0;
	
	CSC1310::String* key_2 = region->getRegionStartKey();
	return key_1->compare(key_2);
}

CSC1310::String* Region::getRegionStartKey()
{
	return &start_key;
}

EndeavorRegionType Region::getRegionType()
{
	return region_type;
}

bool Region::isCityInRegion(uint8 city_id)
{
	return cities->isCityInRegion(city_id);
}

bool Region::canAssignGovernorCard()
{
	return shipping_lane->canAssignGovernorCard();
}

uint8 Region::assignGovernorCard()
{
	return shipping_lane->assignGovernorCard();
}

EndeavorTokenType Region::ship(uint8 player_id, wxBitmap* player_img)
{
	return shipping_lane->ship(player_id, player_img);
}

uint8 Region::findSelectedShip(uint32 x, uint32 y)
{
	return shipping_lane->findSelectedShip(x, y);
}

bool Region::canAttackCity(uint8 player_id, uint8 city_id)
{
	if (!canAttackInRegion(player_id)) return false;
	return cities->canAttackCity(player_id, city_id);
}

bool Region::canAttackInRegion(uint8 player_id)
{
	if (!shipping_lane->isRegionOpen()) return false;
	if (getPlayerPresence(player_id) == 0) return false;
	return cities->canAttackInRegion(player_id);
}

bool Region::attackCity(uint8 player_id, wxBitmap* p_img, uint8 city_id)
{
	return cities->attackCity(player_id, p_img, city_id);
}

EndeavorTokenType Region::occupyCity(uint8 player_id, wxBitmap* player_img, uint8 city_id)
{
	return cities->occupyCity(player_id, player_img, city_id);
}

void Region::getPossibleCitiesToOccupy(CSC1310::ListArray<City>* possible_cities, uint8 player_id)
{
	if (!canOccupyInRegion(player_id)) return;
	cities->getPossibleCitiesToOccupy(possible_cities, player_id);
}

void Region::getPossibleCitiesToAttack(CSC1310::ListArray<City>* possible_cities, uint8 player_id)
{
	if (!canAttackInRegion(player_id)) return;
	cities->getPossibleCitiesToAttack(possible_cities, player_id);
}

void Region::getNextShippingToOccupy(CSC1310::ListArray<Ship>* possible_shipping, uint8 player_id)
{
	shipping_lane->getNextShippingToOccupy(possible_shipping, player_id);
}

bool Region::canOccupyCity(uint8 player_id, uint8 city_id)
{
	if (!canOccupyInRegion(player_id)) return false;
	return cities->canOccupyCity(city_id);
}

bool Region::canOccupyInRegion(uint8 player_id)
{
	if (!shipping_lane->isRegionOpen()) return false;
	if (getPlayerPresence(player_id) == 0) return false;
	return cities->canOccupyInRegion();
}

uint8 Region::getPlayerShippingPresence(uint8 player_id)
{
   return shipping_lane->getPlayerPresence(player_id);
}

uint8 Region::getPlayerPresence(uint8 player_id)
{
   return cities->getPlayerPresence(player_id) + shipping_lane->getPlayerPresence(player_id);
}

uint8 Region::getPlayerIDInCity(uint8 city_id)
{
	return cities->getPlayerIDInCity(city_id);
}

Card* Region::moveGovernorCardToPlayer()
{
	return cards->moveGovernorCardToPlayer();
	
	Card* governor_card = NULL;
	if (canAssignGovernorCard())
	{
		governor_card = cards->moveGovernorCardToPlayer();
	}
	return governor_card;
}

bool Region::canDrawFromRegion(uint8 player_id)
{
	if (!shipping_lane->isRegionOpen()) return false;
	uint8 presence = getPlayerPresence(player_id);
	if (presence == 0) return false;  //can't take the governor card, it is assigned
	uint8 card_level = cards->getCardLevel();
	return (presence >= card_level);
}

void Region::returnCardToRegion(Card* card)
{
	cards->returnCardToRegion(card);
}

Card* Region::takeSelectedCard(uint8 player_id)
{
	return cards->takeSelectedCard(player_id);
}

EndeavorRegionType Region::findSelectedCard(uint32 x, uint32 y)
{
	return cards->findSelectedCard(x, y);
}

uint8 Region::findSelectedCity(uint32 x, uint32 y)
{
	return cities->findSelectedCity(x, y);
}

void Region::draw(wxDC&  dc)
{
   cities->draw(dc);
   shipping_lane->draw(dc);
   cards->draw(dc);
}

Region::Region(EndeavorRegionType r_type, PixelXML& pixel_xml, ImageLoader* image_loader, CSC1310::ListArray<Token>* tokens, CSC1310::Permutation& permute, uint8 city_counter) : start_key(CSC1310::String::i_to_a(city_counter))
{
	region_type = r_type;
	
	switch(region_type)
	{
		case (AFRICA):
		{
			PixelPoint region_card_center = pixel_xml.getPixelCenter("african_cards");
			PixelDimension region_card_dim = pixel_xml.getPixelDimension("african_cards");
			PixelDimension region_card_rot_dim(region_card_dim.getHeight(), region_card_dim.getWidth());
			
			CSC1310::ListArray<PixelPoint>* region_city_centers = pixel_xml.getPixelCentersList("african_cities");
			PixelDimension region_city_dim = pixel_xml.getPixelDimension("african_cities");
			
			CSC1310::ListArray<PixelPoint>* shipping_centers = pixel_xml.getPixelCentersList("african_shipping");
			PixelDimension shipping_dim = pixel_xml.getPixelDimension("african_shipping");
			
			//cities deletes the pixel centers
			cities = new Cities(tokens, permute, region_city_centers, region_city_dim, city_counter);
			//shipping lane deletes the pixel centers
			shipping_lane = new ShippingLane(region_type, tokens, permute, shipping_centers, shipping_dim);
			cards = new Cards(region_type, image_loader, region_card_center, region_card_dim, region_card_rot_dim);
			break;
		}
		
		case (SOUTH_AMERICA):
		{
			PixelPoint region_card_center = pixel_xml.getPixelCenter("south_american_cards");
			PixelDimension region_card_dim = pixel_xml.getPixelDimension("south_american_cards");
			PixelDimension region_card_rot_dim(region_card_dim.getHeight(), region_card_dim.getWidth());
			
			CSC1310::ListArray<PixelPoint>* region_city_centers = pixel_xml.getPixelCentersList("south_american_cities");
			PixelDimension region_city_dim = pixel_xml.getPixelDimension("south_american_cities");
			
			CSC1310::ListArray<PixelPoint>* shipping_centers = pixel_xml.getPixelCentersList("south_american_shipping");
			PixelDimension shipping_dim = pixel_xml.getPixelDimension("south_american_shipping");
			
			//cities deletes the pixel centers
			cities = new Cities(tokens, permute, region_city_centers, region_city_dim, city_counter);
			//shipping lane deletes the pixel centers
			shipping_lane = new ShippingLane(region_type, tokens, permute, shipping_centers, shipping_dim);
			cards = new Cards(region_type, image_loader, region_card_center, region_card_dim, region_card_rot_dim);
			break;
		}
		
		case (CARIBBEAN):
		{
			PixelPoint region_card_center = pixel_xml.getPixelCenter("caribbean_cards");
			PixelDimension region_card_dim = pixel_xml.getPixelDimension("caribbean_cards");
			PixelDimension region_card_rot_dim(region_card_dim.getHeight(), region_card_dim.getWidth());
			
			CSC1310::ListArray<PixelPoint>* region_city_centers = pixel_xml.getPixelCentersList("caribbean_cities");
			PixelDimension region_city_dim = pixel_xml.getPixelDimension("caribbean_cities");
			
			CSC1310::ListArray<PixelPoint>* shipping_centers = pixel_xml.getPixelCentersList("caribbean_shipping");
			PixelDimension shipping_dim = pixel_xml.getPixelDimension("caribbean_shipping");
			
			//cities deletes the pixel centers
			cities = new Cities(tokens, permute, region_city_centers, region_city_dim, city_counter);
			//shipping lane deletes the pixel centers
			shipping_lane = new ShippingLane(region_type, tokens, permute, shipping_centers, shipping_dim);
			cards = new Cards(region_type, image_loader, region_card_center, region_card_dim, region_card_rot_dim);
			break;
		}
		
		case (NORTH_AMERICA):
		{
			PixelPoint region_card_center = pixel_xml.getPixelCenter("north_american_cards");
			PixelDimension region_card_dim = pixel_xml.getPixelDimension("north_american_cards");
			PixelDimension region_card_rot_dim(region_card_dim.getHeight(), region_card_dim.getWidth());
			
			CSC1310::ListArray<PixelPoint>* region_city_centers = pixel_xml.getPixelCentersList("north_american_cities");
			PixelDimension region_city_dim = pixel_xml.getPixelDimension("north_american_cities");
			
			CSC1310::ListArray<PixelPoint>* shipping_centers = pixel_xml.getPixelCentersList("north_american_shipping");
			PixelDimension shipping_dim = pixel_xml.getPixelDimension("north_american_shipping");
			
			//cities deletes the pixel centers
			cities = new Cities(tokens, permute, region_city_centers, region_city_dim, city_counter);
			//shipping lane deletes the pixel centers
			shipping_lane = new ShippingLane(region_type, tokens, permute, shipping_centers, shipping_dim);
			cards = new Cards(region_type, image_loader, region_card_center, region_card_dim, region_card_rot_dim);
			break;
		}
		
		case (INDIA):
		{
			PixelPoint region_card_center = pixel_xml.getPixelCenter("indian_cards");
			PixelDimension region_card_dim = pixel_xml.getPixelDimension("indian_cards");
			PixelDimension region_card_rot_dim(region_card_dim.getHeight(), region_card_dim.getWidth());
			
			CSC1310::ListArray<PixelPoint>* region_city_centers = pixel_xml.getPixelCentersList("indian_cities");
			PixelDimension region_city_dim = pixel_xml.getPixelDimension("indian_cities");
			
			CSC1310::ListArray<PixelPoint>* shipping_centers = pixel_xml.getPixelCentersList("indian_shipping");
			PixelDimension shipping_dim = pixel_xml.getPixelDimension("indian_shipping");
			
			//cities deletes the pixel centers
			cities = new Cities(tokens, permute, region_city_centers, region_city_dim, city_counter);
			//shipping lane deletes the pixel centers
			shipping_lane = new ShippingLane(region_type, tokens, permute, shipping_centers, shipping_dim);
			cards = new Cards(region_type, image_loader, region_card_center, region_card_dim, region_card_rot_dim);
			break;
		}
		
		case (FAR_EAST):
		{
			PixelPoint region_card_center = pixel_xml.getPixelCenter("far_east_cards");
			PixelDimension region_card_dim = pixel_xml.getPixelDimension("far_east_cards");
			PixelDimension region_card_rot_dim(region_card_dim.getHeight(), region_card_dim.getWidth());
			
			CSC1310::ListArray<PixelPoint>* region_city_centers = pixel_xml.getPixelCentersList("far_east_cities");
			PixelDimension region_city_dim = pixel_xml.getPixelDimension("far_east_cities");
			
			CSC1310::ListArray<PixelPoint>* shipping_centers = pixel_xml.getPixelCentersList("far_east_shipping");
			PixelDimension shipping_dim = pixel_xml.getPixelDimension("far_east_shipping");
			
			//cities deletes the pixel centers
			cities = new Cities(tokens, permute, region_city_centers, region_city_dim, city_counter);
			//shipping lane deletes the pixel centers
			shipping_lane = new ShippingLane(region_type, tokens, permute, shipping_centers, shipping_dim);
			cards = new Cards(region_type, image_loader, region_card_center, region_card_dim, region_card_rot_dim);
			break;
		}
	}
}

Region::~Region()
{   
	delete shipping_lane;
	delete cities;
	delete cards;
}

Card* Region::getCard(uint8 card_level)
{
	return cards->getCard(card_level);
}

TiXmlElement* Region::writeXML()
{
   TiXmlElement* region_element = new TiXmlElement("Region");
   
   TiXmlElement* cities_element = cities->writeXML();
   region_element->LinkEndChild(cities_element);
   
   TiXmlElement* shipping_lane_element = shipping_lane->writeXML();
   region_element->LinkEndChild(shipping_lane_element);
   
   TiXmlElement* cards_element = cards->writeXML();
   region_element->LinkEndChild(cards_element);
   
   return region_element;
}

void Region::readXML(TiXmlElement* region_element, wxBitmap** player_images, wxBitmap** token_images)
{
	TiXmlElement* cities_element = region_element->FirstChildElement();
	cities->readXML(cities_element, player_images, token_images);
   
	TiXmlElement* shipping_lane_element = cities_element->NextSiblingElement();
	shipping_lane->readXML(shipping_lane_element, player_images, token_images);
   
	TiXmlElement* cards_element = shipping_lane_element->NextSiblingElement();
	cards->readXML(cards_element);
}
