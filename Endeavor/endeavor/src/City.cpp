#include "City.h"
#include "EndeavorGame.h"

City::City(uint8 city_id, EndeavorTokenType t_type, wxBitmap* token_img, PixelPoint* pixel_center, PixelDimension& pixel_dim)
{
   token_type = t_type;
   player_id = 0;

   occupied = false;
   
   city_draw_img = new DrawImage(token_img, city_id, pixel_dim);
   city_draw_img->showImage(*pixel_center);
}

City::~City()
{
	//the wxBitmap is not deleted
	delete city_draw_img;
}

uint8 City::getCityID()
{
   return city_draw_img->getDrawImageID();
}

uint8 City::getPlayerID()
{
   return player_id;
}

uint8 City::getTokenID()
{
   return token_type;
}

bool City::isOccupied()
{
   return occupied;
}

EndeavorTokenType City::occupyCity(uint8 p_id, wxBitmap* p_img)
{
   occupied = true;
   player_id = p_id;
   
   city_draw_img->setImage(p_img);

   EndeavorTokenType t_type = token_type;
   token_type = INVALID_TOKEN_TYPE;
   return t_type;
}

bool City::isSelectedCity(uint32 x, uint32 y)
{
   return city_draw_img->isSelectedDrawImage(x, y);
}

void City::draw(wxDC&  dc)
{
	city_draw_img->draw(dc);
}

TiXmlElement* City::writeXML()
{
   TiXmlElement* city_element = new TiXmlElement("City");
   TiXmlElement* token_type_element = EndeavorGame::xmlElementFromInteger("token_type", (int) token_type);
   TiXmlElement* player_id_element = EndeavorGame::xmlElementFromInteger("player_id", (int) player_id);

   city_element->LinkEndChild(token_type_element);
   city_element->LinkEndChild(player_id_element);

   return city_element;
}

void City::readXML(TiXmlElement* city_element, wxBitmap** player_images, wxBitmap** token_images)
{
   TiXmlElement* token_type_element = city_element->FirstChildElement();
   token_type = (EndeavorTokenType) EndeavorGame::integerFromXMLElement(token_type_element);

   TiXmlElement* player_id_element = token_type_element->NextSiblingElement();
   player_id = (uint8) EndeavorGame::integerFromXMLElement(player_id_element);
   
   occupied = (player_id > 0);

   if (token_type == INVALID_TOKEN_TYPE)
   {
      city_draw_img->setImage(player_images[player_id - 1]);
   }
   else
   {
      city_draw_img->setImage(token_images[token_type - 1]);
   }
}
