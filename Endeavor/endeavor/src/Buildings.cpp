#include "Buildings.h"
#include "EndeavorGame.h"

#include "ListArrayIterator.h"
#include "ListLinkedIterator.h"

#include "ImageLoader.h"
#include "PixelPoint.h"
#include "PixelDimension.h"

//return all available buildings at a specified industry level and lower
//these two methods may make a good exercise to add to lab 3
uint8* Buildings::getAvailableBuildings(uint8 industry_level)
{
   uint8* available_buildings = new uint8[15];
   for (int i = 0; i < 15; i++)
   {
      available_buildings[i] = 0;
   }

   uint8 lowest_level = getLowestLevelAvailable();
   //player must choose from a higher level (the lowest with buildings)
   //if there are no buildings at the player's industry level (or 
   if (lowest_level > industry_level)  
   {
      getBuildingsAtSpecifiedLevel(available_buildings, lowest_level);
      return available_buildings;
   }

   for (int i = 1; i <= industry_level; i++)
   {
      getBuildingsAtSpecifiedLevel(available_buildings, i);
   }

   return available_buildings;
}

void Buildings::getBuildingsAtSpecifiedLevel(uint8* available_buildings, uint8 level)
{
	CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      EndeavorBuildingType building_id = building->getBuildingID();
      uint8 building_level = (building_id - 1)/3 + 1;
      if (building_level == level)
      {
		  int current_count = available_buildings[building_id - 1];
          available_buildings[building_id - 1] = current_count + 1;
      }
   }

   delete building_iter;
}

uint8 Buildings::getLowestLevelAvailable()
{
   uint8 lowest_level = 6;

   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      EndeavorBuildingType building_id = building->getBuildingID();
      uint8 building_level = (building_id - 1)/3 + 1;
      if (building_level < lowest_level)
      {
         lowest_level = building_level;
      }
   }

   delete building_iter;
   return lowest_level;
}

Building* Buildings::removeBuilding(EndeavorBuildingType building_id)
{
   int num_buildings = buildings->size();
   for (int i = 1; i <= num_buildings; i++)
   {
      Building* building = buildings->get(i);
      if (building->getBuildingID() == building_id)
      {
         buildings->remove(i);
         return building;
      }
   }

   return NULL;
}

EndeavorBuildingType Buildings::findSelectedBuilding(uint32 x, uint32 y)
{
   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      if (building->isSelectedBuilding(x, y))
      {
         delete building_iter;
         return building->getBuildingID();
      }
   }

   delete building_iter;
   return INVALID_BUILDING_TYPE;  
}

void Buildings::draw(wxDC&  dc)
{
   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      building->draw(dc);
   }

   delete building_iter;
}

Buildings::Buildings(PixelXML& pixel_xml, ImageLoader* image_loader)
{
   buildings = new CSC1310::ListLinked<Building>();
   all_buildings = new CSC1310::ListArray<Building>();
   uint8 unique_id = 1;
   
   CSC1310::ListArray<PixelPoint>* building_centers = pixel_xml.getPixelCentersList("buildings_available");
   PixelDimension pixel_dim = pixel_xml.getPixelDimension("buildings_available");
   PixelDimension worker_dim = pixel_xml.getPixelDimension("player_marker");
   int building_counter = 1;
   
   building_images = new wxBitmap*[16];
   wxBitmap* colonial_house_img = image_loader->loadImageRGBA("colonial_house");
   building_images[0] = colonial_house_img;
   
   //level 0 buildings (colonial house)
   //every player starts with a colonial house, so need five of these
   for (int i = 1; i <= 5; i++)
   {
      Building* b = new Building(0, unique_id++, colonial_house_img, NULL, pixel_dim, worker_dim, true, 0, 0, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //industry level 1 buildings (5 each)
   int num_buildings_at_this_level = 5;

   //market
   wxBitmap* market_img = image_loader->loadImageRGBA("market");
   building_images[1] = market_img;

   PixelPoint* pixel_center = building_centers->get(1);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(1, unique_id++, market_img, pixel_center, pixel_dim, worker_dim, true, 0, 0, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //shipyard
   wxBitmap* shipyard_img = image_loader->loadImageRGBA("shipyard");
   building_images[2] = shipyard_img;

   pixel_center = building_centers->get(2);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(2, unique_id++, shipyard_img, pixel_center, pixel_dim, worker_dim, true, 0, 1, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //workshop
   wxBitmap* workshop_img = image_loader->loadImageRGBA("workshop");
   building_images[3] = workshop_img;

   pixel_center = building_centers->get(3);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(3, unique_id++, workshop_img, pixel_center, pixel_dim, worker_dim, false, 2, 0, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //industry level 2 buildings (4 each)
   num_buildings_at_this_level = 4;

   //bank
   wxBitmap* bank_img = image_loader->loadImageRGBA("bank");
   building_images[4] = bank_img;
   
   pixel_center = building_centers->get(4);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(4, unique_id++, bank_img, pixel_center, pixel_dim, worker_dim, false, 0, 0, 2, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //barracks
   wxBitmap* barracks_img = image_loader->loadImageRGBA("barracks");
   building_images[5] = barracks_img;

   pixel_center = building_centers->get(5);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(5, unique_id++, barracks_img, pixel_center, pixel_dim, worker_dim, true, 0, 0, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //guild hall
   wxBitmap* guild_hall_img = image_loader->loadImageRGBA("guild_hall");
   building_images[6] = guild_hall_img;

   pixel_center = building_centers->get(6);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(6, unique_id++, guild_hall_img, pixel_center, pixel_dim, worker_dim, true, 0, 0, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //industry level 3 buildings (3 each)
   num_buildings_at_this_level = 3;

   //docks
   wxBitmap* docks_img = image_loader->loadImageRGBA("docks");
   building_images[7] = docks_img;
   
   pixel_center = building_centers->get(7);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(7, unique_id++, docks_img, pixel_center, pixel_dim, worker_dim, true, 0, 0, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //fortress
   wxBitmap* fortress_img = image_loader->loadImageRGBA("fortress");
   building_images[8] = fortress_img;

   pixel_center = building_centers->get(8);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(8, unique_id++, fortress_img, pixel_center, pixel_dim, worker_dim, true, 0, 0, 0, 1, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //theatre
   wxBitmap* theatre_img = image_loader->loadImageRGBA("theatre");
   building_images[9] = theatre_img;

   pixel_center = building_centers->get(9);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(9, unique_id++, theatre_img, pixel_center, pixel_dim, worker_dim, false, 0, 2, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //industry level 4 buildings (2 each)
   num_buildings_at_this_level = 2;

   //cartographer
   wxBitmap* cartographer_img = image_loader->loadImageRGBA("cartographer");
   building_images[10] = cartographer_img;

   pixel_center = building_centers->get(10);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(10, unique_id++, cartographer_img, pixel_center, pixel_dim, worker_dim, true, 0, 0, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //trade office
   wxBitmap* trade_office_img = image_loader->loadImageRGBA("trade_office");
   building_images[11] = trade_office_img;

   pixel_center = building_centers->get(11);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(11, unique_id++, trade_office_img, pixel_center, pixel_dim, worker_dim, true, 0, 0, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //university
   wxBitmap* university_img = image_loader->loadImageRGBA("university");
   building_images[12] = university_img;

   pixel_center = building_centers->get(12);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(12, unique_id++, university_img, pixel_center, pixel_dim, worker_dim, false, 0, 0, 0, 0, 3);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //industry level 5 buildings (1 each)
   num_buildings_at_this_level = 1;

   //exchange
   wxBitmap* exchange_img = image_loader->loadImageRGBA("exchange");
   building_images[13] = exchange_img;

   pixel_center = building_centers->get(13);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(13, unique_id++, exchange_img, pixel_center, pixel_dim, worker_dim, true, 0, 0, 2, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //museum
   wxBitmap* museum_img = image_loader->loadImageRGBA("museum");
   building_images[14] = museum_img;

   pixel_center = building_centers->get(14);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(14, unique_id++, museum_img, pixel_center, pixel_dim, worker_dim, true, 0, 2, 0, 0, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }

   //parliament
   wxBitmap* parliament_img = image_loader->loadImageRGBA("parliament");
   building_images[15] = parliament_img;

   pixel_center = building_centers->get(15);
   for (int i = 1; i <= num_buildings_at_this_level; i++)
   {
      Building* b = new Building(15, unique_id++, parliament_img, pixel_center, pixel_dim, worker_dim, true, 0, 0, 0, 2, 0);
      buildings->add(b);
	  all_buildings->add(b);
   }
   
   CSC1310::ListArrayIterator<PixelPoint>* point_iter = building_centers->iterator();
   while(point_iter->hasNext())
   {
      PixelPoint* pixel_center = point_iter->next();
      delete pixel_center;
   }
   delete point_iter;
   delete building_centers;
}

Buildings::~Buildings()
{
   CSC1310::ListLinkedIterator<Building>* building_iter = buildings->iterator();
   while(building_iter->hasNext())
   {
      Building* building = building_iter->next();
      delete building;
   }
   delete building_iter;
   delete buildings;
   delete all_buildings;
   
   for (int i = 0; i < 16; i++)
   {
	   if (building_images[i])
	   {

		   delete building_images[i];
	   }
   }
   delete[] building_images;
}

Building* Buildings::getSpecificBuilding(uint8 unique_id)
{
	return all_buildings->get(unique_id);
}

TiXmlElement* Buildings::writeXML()
{
   TiXmlElement* buildings_element = new TiXmlElement("Buildings");
   
   CSC1310::ListLinkedIterator<Building>* buildings_iter = buildings->iterator();
	while(buildings_iter->hasNext())
	{
		Building* building = buildings_iter->next();
		TiXmlElement* building_element = building->writeXML();
		buildings_element->LinkEndChild(building_element);
	}
	delete buildings_iter;

   return buildings_element;
}

void Buildings::readXML(TiXmlElement* buildings_element)
{	  
	buildings->removeAll();
	
   TiXmlElement* building_element = buildings_element->FirstChildElement();
   while(building_element != NULL)
   {
	   TiXmlElement* building_unique_id_element = building_element->FirstChildElement();
	   uint8 unique_id = (uint8) EndeavorGame::integerFromXMLElement(building_unique_id_element);

	   Building* building = getSpecificBuilding(unique_id);
	   building->readXML(building_element);
	   buildings->add(building);
	   building_element = building_element->NextSiblingElement();
   }
}
