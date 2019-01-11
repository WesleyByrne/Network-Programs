#include "Cities.h"
#include "EndeavorGame.h"

#include "ListArrayIterator.h"

uint8 Cities::computeCityGlory(uint8 player_id)
{
	uint8 city_glory = 0;
	CSC1310::ListArrayIterator<City>* cities_iter = cities->iterator();
   while(cities_iter->hasNext())
   {
      City* city = cities_iter->next();
      if (city->getPlayerID() == player_id)
      {
         city_glory++;
		 uint8 city_id = city->getCityID();
		 if (city_id == 13 || city_id == 28)
		 {
			 city_glory++;
		 }
      }
   }
   delete cities_iter;
   
	return city_glory;
}
		
bool Cities::isCityInRegion(uint8 city_id)
{
	return (city_id >= first_city_id) && (city_id < first_city_id + num_cities_in_region);
}

uint8 Cities::findSelectedCity(uint32 x, uint32 y)
{
   CSC1310::ListArrayIterator<City>* iter = cities->iterator();
   while(iter->hasNext())
   {
      City* city = iter->next();
      if (city->isSelectedCity(x, y))
      {
         delete iter;
         return city->getCityID();
      }
   }
   delete iter;

   return 0;  
}

uint8 Cities::getPlayerPresence(uint8 player_id)
{
   uint8 player_presence = 0;

   CSC1310::ListArrayIterator<City>* city_iter = cities->iterator();
   while (city_iter->hasNext())
   {
      City* city = city_iter->next();
      if (city->getPlayerID() == player_id)
      {
         player_presence++;
      }
   }
   delete city_iter;

   return player_presence;
}

bool Cities::canAttackInRegion(uint8 player_id)
{
   CSC1310::ListArrayIterator<City>* city_iter = cities->iterator();
   while (city_iter->hasNext())
   {
      City* city = city_iter->next();
      bool occupied = city->isOccupied();
      uint8 other_player_id = city->getPlayerID();
      if (occupied && (other_player_id != player_id))
      {
         delete city_iter;
         return true;
      }
   }
   delete city_iter;

   return false;
}

bool Cities::canAttackCity(uint8 player_id, uint8 city_id)
{
	if (!isCityInRegion(city_id)) return false;
	uint8 city_index = city_id - first_city_id + 1;
	
	City* city = cities->get(city_index);
	return city->isOccupied() && (player_id != city->getPlayerID());
}

bool Cities::attackCity(uint8 player_id, wxBitmap* p_img, uint8 city_id)
{
   CSC1310::ListArrayIterator<City>* city_iter = cities->iterator();
   while (city_iter->hasNext())
   {
      City* city = city_iter->next();
      if (city->getCityID() == city_id)
      {
         bool occupied = city->isOccupied();
         uint8 other_player_id = city->getPlayerID();

         if (!occupied || (other_player_id == player_id))
         {
            delete city_iter;
            return false;
         }

         city->occupyCity(player_id, p_img);
         delete city_iter;
         return true;
      }
   }
   delete city_iter;

   return false;
}

bool Cities::canOccupyInRegion()
{
   CSC1310::ListArrayIterator<City>* city_iter = cities->iterator();
   while (city_iter->hasNext())
   {
      City* city = city_iter->next();
      if (!city->isOccupied())
      {
         delete city_iter;
         return true;
      }
   }
   delete city_iter;

   return false;
}

bool Cities::canOccupyCity(uint8 city_id)
{
	if (!isCityInRegion(city_id)) return false;
	uint8 city_index = city_id - first_city_id + 1;

	City* city = cities->get(city_index);
	return !city->isOccupied();
}

void Cities::getPossibleCitiesToAttack(CSC1310::ListArray<City>* possible_cities, uint8 player_id)
{
	CSC1310::ListArrayIterator<City>* cities_iter = cities->iterator();
   while(cities_iter->hasNext())
   {
	   City* city = cities_iter->next();
	   if(canAttackCity(player_id, city->getCityID()))
	   {
		   possible_cities->add(city);
	   }
   }
   delete cities_iter;
}

void Cities::getPossibleCitiesToOccupy(CSC1310::ListArray<City>* possible_cities, uint8 player_id)
{
	CSC1310::ListArrayIterator<City>* cities_iter = cities->iterator();
   while(cities_iter->hasNext())
   {
	   City* city = cities_iter->next();
	   if (canOccupyCity(city->getCityID()))
	   {
		   possible_cities->add(city);
	   }
   }
   delete cities_iter;
}

EndeavorTokenType Cities::occupyCity(uint8 player_id, wxBitmap* player_img, uint8 city_id)
{
	//is already known to be a legal move
	uint8 city_index = city_id - first_city_id + 1;
	
	City* city = cities->get(city_index);
	if (!city->isOccupied())
	{
		//return the token type that was in the city
		return city->occupyCity(player_id, player_img);  
	}
         
	return INVALID_TOKEN_TYPE;  
}

uint8 Cities::getPlayerIDInCity(uint8 city_id)
{
	if (!isCityInRegion(city_id)) return 0;
	uint8 city_index = city_id - first_city_id + 1;
   uint8 player_id = 0;
   
   return cities->get(city_index)->getPlayerID();
}

void Cities::draw(wxDC&  dc)
{
   CSC1310::ListArrayIterator<City>* iter = cities->iterator();
   while(iter->hasNext())
   {
      City* city = iter->next();
      city->draw(dc);
   }
   delete iter;
}

Cities::Cities(CSC1310::ListArray<Token>* tokens, CSC1310::Permutation& permute, CSC1310::ListArray<PixelPoint>* region_city_centers, PixelDimension& region_city_dim, uint8 city_counter)
{
	cities = new CSC1310::ListArray<City>();
	
	first_city_id = city_counter;
	num_cities_in_region = region_city_centers->size();
	
	CSC1310::ListArrayIterator<PixelPoint>* region_cities_iter = region_city_centers->iterator();
	while(region_cities_iter->hasNext())
	{
		PixelPoint* region_city_center = region_cities_iter->next();
		   
		uint8 token_index = permute.next();
		Token* token = tokens->get(token_index);
		EndeavorTokenType token_type = token->getTokenType();
		wxBitmap* token_img = token->getTokenImage();
			   
		City* city = new City(city_counter, token_type, token_img, region_city_center, region_city_dim);
		cities->add(city);

		city_counter++;
		delete region_city_center;
	}
	delete region_cities_iter;
	delete region_city_centers;
}

Cities::~Cities()
{
   CSC1310::ListArrayIterator<City>* city_iter = cities->iterator();
   while(city_iter->hasNext())
   {
      City* city = city_iter->next();
      delete city;
   }
   delete city_iter;
   delete cities;
}

TiXmlElement* Cities::writeXML()
{
   TiXmlElement* cities_element = new TiXmlElement("Cities");
   
   TiXmlElement* first_city_id_element = EndeavorGame::xmlElementFromInteger("first_city_id", (int) first_city_id);
   TiXmlElement* num_cities_in_region_element = EndeavorGame::xmlElementFromInteger("num_cities_in_region", (int) num_cities_in_region);

   cities_element->LinkEndChild(first_city_id_element);
   cities_element->LinkEndChild(num_cities_in_region_element);
   
   CSC1310::ListArrayIterator<City>* cities_iter = cities->iterator();
   while(cities_iter->hasNext())
   {
	   City* city = cities_iter->next();
	   TiXmlElement* city_element = city->writeXML();
	   cities_element->LinkEndChild(city_element);
   }
   delete cities_iter;

   return cities_element;
}

void Cities::readXML(TiXmlElement* cities_element, wxBitmap** player_images, wxBitmap** token_images)
{
   TiXmlElement* first_city_id_element = cities_element->FirstChildElement();
   first_city_id = (uint8) EndeavorGame::integerFromXMLElement(first_city_id_element);

   TiXmlElement* num_cities_in_region_element = first_city_id_element->NextSiblingElement();
   num_cities_in_region = (uint8) EndeavorGame::integerFromXMLElement(num_cities_in_region_element);
   
   TiXmlElement* city_element = num_cities_in_region_element->NextSiblingElement();
   
   CSC1310::ListArrayIterator<City>* city_iter = cities->iterator();
   while(city_iter->hasNext())
   {
	   City* city = city_iter->next();
	   city->readXML(city_element, player_images, token_images);
	   city_element = city_element->NextSiblingElement();
   }
   delete city_iter;
}
