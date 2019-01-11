#include "Building.h"
#include "EndeavorGame.h"

#include "PixelPoint.h"
#include "PixelDimension.h"

Building::Building(uint8 building_id, uint8 u_id, wxBitmap* building_img, PixelPoint* pixel_center, PixelDimension& pixel_dim, PixelDimension& worker_dim, bool activate, uint8 industry_, uint8 culture_, uint8 finance_, uint8 politics_, uint8 glory_)
{
	unique_id = u_id;
	
   can_activate = activate;
   is_activated = false;

   industry = industry_;
   culture = culture_;
   finance = finance_;
   politics = politics_;
   glory = glory_;
   
   player_id = 0;
   
   building_draw_img = new DrawImage(building_img, building_id, pixel_dim);
   if (pixel_center)
   {
		building_draw_img->showImage(*pixel_center);
   }
   
   //worker token will be placed in the active circle on the building
   activated_draw_img = new DrawImage(NULL, building_id, worker_dim);
}

Building::~Building()
{
	//the wxBitmap is not deleted
	delete building_draw_img;
	delete activated_draw_img;
}

EndeavorBuildingType Building::getBuildingID()
{
	return (EndeavorBuildingType) building_draw_img->getDrawImageID();
}

uint8 Building::getIndustry()
{
   return industry;
}

uint8 Building::getFinance()
{
   return finance;
}

uint8 Building::getCulture()
{
   return culture;
}

uint8 Building::getPolitics()
{
   return politics;
}

uint8 Building::getGlory()
{
   return glory;
}

void Building::setPlayerImage(uint8 p_id, wxBitmap* worker_img)
{
	player_id = p_id;
	activated_draw_img->setImage(worker_img);
}

void Building::activate()
{
	if (can_activate)
	{
		is_activated = true;
	}
}

bool Building::canActivate()
{
	return can_activate;
}

bool Building::isActivated()
{
	return is_activated;
}

void Building::makePayment()
{
	is_activated = false;
}

void Building::setBuildingLocation(PixelPoint& pixel_center)
{
	PixelPoint activated_center(pixel_center.getX() + 25, pixel_center.getY());
	activated_draw_img->showImage(activated_center);
	building_draw_img->showImage(pixel_center);
}

bool Building::isSelectedActionCircle(uint32 x, uint32 y)
{
	return activated_draw_img->isSelectedDrawImage(x, y);
}

bool Building::isSelectedBuilding(uint32 x, uint32 y)
{
	return building_draw_img->isSelectedDrawImage(x, y);
}

uint8 Building::getUniqueID()
{
	return unique_id;
}

void Building::draw(wxDC&  dc)
{
	building_draw_img->draw(dc);
	if (isActivated())  //need to show the worker token if the building is activated
	{
	   activated_draw_img->draw(dc);
	}
}

TiXmlElement* Building::writeXML()
{
   TiXmlElement* building_element = new TiXmlElement("Building");
   
   TiXmlElement* unique_id_element = EndeavorGame::xmlElementFromInteger("unique_id", (int) unique_id);
   TiXmlElement* player_id_element = EndeavorGame::xmlElementFromInteger("player_id", (int) player_id);
   TiXmlElement* is_activated_element = EndeavorGame::xmlElementFromInteger("is_activated", (int) is_activated);

   building_element->LinkEndChild(unique_id_element);
   building_element->LinkEndChild(player_id_element);
   building_element->LinkEndChild(is_activated_element);

   return building_element;
}

void Building::readXML(TiXmlElement* building_element)
{
	TiXmlElement* unique_id_element = building_element->FirstChildElement();
	unique_id = (uint8) EndeavorGame::integerFromXMLElement(unique_id_element);
	
	TiXmlElement* player_id_element = unique_id_element->NextSiblingElement();
	player_id = (uint8) EndeavorGame::integerFromXMLElement(player_id_element);
	
	TiXmlElement* is_activated_element = player_id_element->NextSiblingElement();
	is_activated = (bool) EndeavorGame::integerFromXMLElement(is_activated_element);
}
