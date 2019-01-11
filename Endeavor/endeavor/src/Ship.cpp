#include "Ship.h"
#include "EndeavorGame.h"

Ship::Ship(uint8 s_id, EndeavorTokenType t_type, wxBitmap* token_img, PixelPoint* pixel_center, PixelDimension& pixel_dim) : ship_img_center(*pixel_center)
{
   token_type = t_type;
   player_id = 0;

   occupied = false;

   ship_draw_img = new DrawImage(token_img, s_id, pixel_dim);
   ship_draw_img->showImage(ship_img_center);
}

//constructor for additional shipping locations (no token available)
Ship::Ship(uint8 s_id, PixelPoint* pixel_center, PixelDimension& pixel_dim) : ship_img_center(*pixel_center)
{ 
   token_type = INVALID_TOKEN_TYPE;
   player_id = 0;

   occupied = false;

   ship_draw_img = new DrawImage(NULL, s_id, pixel_dim);
   //ship_draw_img->showImage(*pixel_center);
}

Ship::~Ship()
{
	delete ship_draw_img;
}

uint8 Ship::getPlayerID()
{
   return player_id;
}

uint8 Ship::getShipID()
{
   return ship_draw_img->getDrawImageID();
}

EndeavorTokenType Ship::getTokenID()
{
   return token_type;
}

bool Ship::isOccupied()
{
   return occupied;
}

EndeavorTokenType Ship::occupyShip(uint8 p_id, wxBitmap* p_img)
{
   occupied = true;
   player_id = p_id;
   
   ship_draw_img->setImage(p_img);
   //needed for when additional shipping locations are occupied
   if (token_type == INVALID_TOKEN_TYPE)
   {
		ship_draw_img->showImage(ship_img_center);
   }

   EndeavorTokenType t_type = token_type;
   token_type = INVALID_TOKEN_TYPE;
   return t_type;
}

bool Ship::isSelectedShip(uint32 x, uint32 y)
{
	return ship_draw_img->isSelectedDrawImage(x, y);
}

void Ship::draw(wxDC&  dc)
{
	//more complicated due to the additional shipping locations
	if (token_type != INVALID_TOKEN_TYPE || player_id > 0)
	{
		ship_draw_img->draw(dc);
	}
}

TiXmlElement* Ship::writeXML()
{
   TiXmlElement* ship_element = new TiXmlElement("Ship");
   TiXmlElement* token_type_element = EndeavorGame::xmlElementFromInteger("token_type", (int) token_type);
   TiXmlElement* player_id_element = EndeavorGame::xmlElementFromInteger("player_id", (int) player_id);
   //TiXmlElement* occupied_element = Utils::xmlElementFromInteger("occupied", occupied);

   ship_element->LinkEndChild(token_type_element);
   ship_element->LinkEndChild(player_id_element);
   //ship_element->LinkEndChild(occupied_element);

   return ship_element;
}

void Ship::readXML(TiXmlElement* ship_element, wxBitmap** player_images, wxBitmap** token_images)
{
   TiXmlElement* token_type_element = ship_element->FirstChildElement();
   token_type = (EndeavorTokenType) EndeavorGame::integerFromXMLElement(token_type_element);

   TiXmlElement* player_id_element = token_type_element->NextSiblingElement();
   player_id = (uint8) EndeavorGame::integerFromXMLElement(player_id_element);
   
   occupied = (player_id > 0);

   if (token_type == INVALID_TOKEN_TYPE)
   {
      ship_draw_img->setImage(player_images[player_id - 1]);
	  ship_draw_img->showImage(ship_img_center);
   }
   else
   {
      ship_draw_img->setImage(token_images[token_type - 1]);
   }
}
