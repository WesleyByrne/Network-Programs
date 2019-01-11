#include "Connection.h"
#include "EndeavorGame.h"

#include "PixelPoint.h"
#include "PixelDimension.h"

void Connection::breakControlOfConnection()
{
	control_id = 0;
}

EndeavorTokenType Connection::takeControlOfConnection(uint8 player_id, wxBitmap* player_circle_img)
{
	control_id = player_id;
	EndeavorTokenType control_token_type = token_type;
	token_type = INVALID_TOKEN_TYPE;
	connection_draw_img->setImage(player_circle_img);
	return control_token_type;
}
  
Connection::Connection(uint8 c_1_id, uint8 c_2_id, EndeavorTokenType t_id, wxBitmap* token_img, PixelPoint* pixel_center, PixelDimension& pixel_dim) : connection_key_1(String::i_to_a(c_1_id)), connection_key_2(String::i_to_a(c_2_id))
{
	city_1_id = c_1_id;
	city_2_id = c_2_id;
	control_id = 0;
	token_type = t_id;

	connection_draw_img = new DrawImage(token_img, (uint8) t_id, pixel_dim);
	connection_draw_img->showImage(*pixel_center);
}

Connection::~Connection()
{
	delete connection_draw_img;
}

uint8 Connection::getCity1ID()
{
	return city_1_id;
}

uint8 Connection::getCity2ID()
{
	return city_2_id;
}

uint8 Connection::getControlID()
{
   return control_id;
}

void Connection::draw(wxDC&  dc)
{
   //if the token has not been taken, draw it
   if (token_type != INVALID_TOKEN_TYPE || control_id > 0)  
   {
	   connection_draw_img->draw(dc);
   }
}

String* Connection::getConnectionKey1()
{
	return &connection_key_1;
}

String* Connection::getConnectionKey2()
{
	return &connection_key_2;
}

int Connection::compareConnectionsByFirstCity(Connection* connection_1, Connection* connection_2)
{
	String* key = connection_1->getConnectionKey1();
	return compareConnectionsByKeyAndFirstCity(key, connection_2);
}

int Connection::compareConnectionsBySecondCity(Connection* connection_1, Connection* connection_2)
{
	String* key = connection_1->getConnectionKey2();
	return compareConnectionsByKeyAndSecondCity(key, connection_2);
}

int Connection::compareConnectionsByKeyAndFirstCity(String* connection_key, Connection* connection)
{
	String* first_key = connection->getConnectionKey1();
	return connection_key->compare(first_key);
}

int Connection::compareConnectionsByKeyAndSecondCity(String* connection_key, Connection* connection)
{
	String* second_key = connection->getConnectionKey2();
	return connection_key->compare(second_key);
}

TiXmlElement* Connection::writeXML()
{
   TiXmlElement* connection_element = new TiXmlElement("Connection");
   TiXmlElement* token_type_element = EndeavorGame::xmlElementFromInteger("token_type", (int) token_type);
   TiXmlElement* player_id_element = EndeavorGame::xmlElementFromInteger("player_id", (int) control_id);

   connection_element->LinkEndChild(token_type_element);
   connection_element->LinkEndChild(player_id_element);

   return connection_element;
}

void Connection::readXML(TiXmlElement* connection_element, wxBitmap** player_images, wxBitmap** token_images)
{
   TiXmlElement* token_type_element = connection_element->FirstChildElement();
   token_type = (EndeavorTokenType) EndeavorGame::integerFromXMLElement(token_type_element);

   TiXmlElement* player_id_element = token_type_element->NextSiblingElement();
   control_id = (uint8) EndeavorGame::integerFromXMLElement(player_id_element);

   if (token_type == INVALID_TOKEN_TYPE)
   {
      connection_draw_img->setImage(player_images[control_id - 1]);
   }
   else
   {
      connection_draw_img->setImage(token_images[token_type - 1]);
   }
}
