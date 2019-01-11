#include "ShippingLane.h"
#include "EndeavorGame.h"

#include "ListDoublyLinkedIterator.h"

void ShippingLane::getNextShippingToOccupy(CSC1310::ListArray<Ship>* possible_shipping, uint8 player_id)
{
	if (!isRegionOpen())
	{
		Ship* ship = shipping_lane->get(ship_cursor);
		possible_shipping->add(ship);
	}
}

bool ShippingLane::isRegionOpen()
{
	return (ship_cursor > num_regular_shipping_locations);
}

uint8 ShippingLane::getNumOpenRegularLocations()
{
	return (num_regular_shipping_locations - ship_cursor + 1);
}

uint8 ShippingLane::getPlayerPresence(uint8 player_id)
{
	uint8 player_shipping_presence = 0;
	CSC1310::ListDoublyLinkedIterator<Ship>* shipping_lane_iter = shipping_lane->iterator();
	while(shipping_lane_iter->hasNext())
	{
		Ship* ship = shipping_lane_iter->next();
		if (ship->getPlayerID() == player_id)
		{
			player_shipping_presence++;
		}
	}
	delete shipping_lane_iter;

	return player_shipping_presence;
}

bool ShippingLane::canAssignGovernorCard()
{
	//the governor card is awarded at a specific time
	return (ship_cursor == num_regular_shipping_locations + 1);
}

//returns the id of the player who has won the governor card for the corresponding region
uint8 ShippingLane::assignGovernorCard()
{
	if (!canAssignGovernorCard())
	{
		return 0;
	}
	
	uint8* player_ship_count = new uint8[5];
	for (int i = 0; i < 5; i++)
	{
		player_ship_count[i] = 0;
	}
	
	CSC1310::ListDoublyLinkedIterator<Ship>* shipping_lane_iter = shipping_lane->iterator();
	while(shipping_lane_iter->hasNext())
	{
		Ship* ship = shipping_lane_iter->next();
		player_ship_count[ship->getPlayerID() - 1]++;
	}
	delete shipping_lane_iter;
	
	uint8 governor_id = 0;
	uint8 max_ship_count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (player_ship_count[i] > max_ship_count)
		{
			max_ship_count = player_ship_count[i];
			governor_id = i + 1;
		}
		//player closer to governor card wins the tie
		else if (player_ship_count[i] == max_ship_count && max_ship_count > 0)
		{
			uint8 test_player = i + 1;
			//this is efficient for a doubly linked list that stays at the most recent location
			//spatial locality of reference
			for (int j = num_regular_shipping_locations; j >= 1; j--)
			{
				Ship* ship = shipping_lane->get(j);
				if (ship->getPlayerID() == test_player)
				{
					governor_id = test_player;
					break;
				}
				else if (ship->getPlayerID() == governor_id)
				{
					break;
				}
			}
		}
	}

	return governor_id;
}

EndeavorTokenType ShippingLane::ship(uint8 player_id, wxBitmap* player_img)
{
	Ship* ship = shipping_lane->get(ship_cursor);
	EndeavorTokenType token_type = ship->occupyShip(player_id, player_img);
	ship_cursor++;
	return token_type;
}

uint8 ShippingLane::findSelectedShip(uint32 x, uint32 y)
{
	CSC1310::ListDoublyLinkedIterator<Ship>* shipping_lane_iter = shipping_lane->iterator();
	while(shipping_lane_iter->hasNext())
	{
		Ship* ship = shipping_lane_iter->next();
		if (ship->isSelectedShip(x, y))
		{
			uint8 ship_id = ship->getShipID();
			if (ship_id == ship_cursor && ship_cursor <= num_regular_shipping_locations)
			{
				return ship->getShipID();
			}
			//additional shipping selected by clicking on the last regular shipping location
			else if (ship_id == num_regular_shipping_locations && ship_cursor > num_regular_shipping_locations)
			{
				return ship->getShipID();
			}
			else
			{
				return 0;
			}
		}
	}
	delete shipping_lane_iter;
	return 0;
}

void ShippingLane::draw(wxDC&  dc)
{
	CSC1310::ListDoublyLinkedIterator<Ship>* shipping_lane_iter = shipping_lane->iterator();
	while(shipping_lane_iter->hasNext())
	{
		Ship* ship = shipping_lane_iter->next();
		ship->draw(dc);
	}
	delete shipping_lane_iter;
}

ShippingLane::ShippingLane(EndeavorRegionType region_type, CSC1310::ListArray<Token>* tokens, CSC1310::Permutation& permute, CSC1310::ListArray<PixelPoint>* pixel_centers, PixelDimension& pixel_dim)
{
	shipping_lane = new CSC1310::ListDoublyLinked<Ship>();
	
	num_regular_shipping_locations = pixel_centers->size() - 5;
	for (int i = 1; i <= num_regular_shipping_locations; i++)  //process regular shipping lane locations
	{
		PixelPoint* pixel_center = pixel_centers->get(i);
		
		uint8 token_index = permute.next();
		Token* token = tokens->get(token_index);
		EndeavorTokenType token_type = token->getTokenType();
		wxBitmap* token_img = token->getTokenImage();
		
		Ship* ship = new Ship(i, token_type, token_img, pixel_center, pixel_dim);
		ship->setRegionType(region_type);
		shipping_lane->add(ship);
		delete pixel_center;
	}
	
	for (int i = 1; i <= 5; i++)  //process additional shipping lane locations
	{
		int temp = i + num_regular_shipping_locations;
		PixelPoint* pixel_center = pixel_centers->get(temp);
		
		Ship* ship = new Ship(temp, pixel_center, pixel_dim);
		shipping_lane->add(ship);
		delete pixel_center;
	}
	delete pixel_centers;
	
	ship_cursor = 1;
}

ShippingLane::~ShippingLane()
{
	CSC1310::ListDoublyLinkedIterator<Ship>* shipping_lane_iter = shipping_lane->iterator();
	while(shipping_lane_iter->hasNext())
	{
		Ship* ship = shipping_lane_iter->next();
		delete ship;
	}
	delete shipping_lane_iter;
	delete shipping_lane;
}

TiXmlElement* ShippingLane::writeXML()
{
   TiXmlElement* shipping_lane_element = new TiXmlElement("ShippingLane");
   
   TiXmlElement* ship_cursor_element = EndeavorGame::xmlElementFromInteger("ship_cursor", (int) ship_cursor);
   TiXmlElement* num_regular_shipping_element = EndeavorGame::xmlElementFromInteger("num_regular_shipping", (int) num_regular_shipping_locations);

   shipping_lane_element->LinkEndChild(ship_cursor_element);
   shipping_lane_element->LinkEndChild(num_regular_shipping_element);
   
   CSC1310::ListDoublyLinkedIterator<Ship>* ship_iter = shipping_lane->iterator();
   while(ship_iter->hasNext())
   {
	   Ship* ship = ship_iter->next();
	   TiXmlElement* ship_element = ship->writeXML();
	   shipping_lane_element->LinkEndChild(ship_element);
   }
   delete ship_iter;

   return shipping_lane_element;
}

void ShippingLane::readXML(TiXmlElement* shipping_lane_element, wxBitmap** player_images, wxBitmap** token_images)
{
   TiXmlElement* ship_cursor_element = shipping_lane_element->FirstChildElement();
   ship_cursor = (uint8) EndeavorGame::integerFromXMLElement(ship_cursor_element);

   TiXmlElement* num_regular_shipping_element = ship_cursor_element->NextSiblingElement();
   num_regular_shipping_locations = (uint8) EndeavorGame::integerFromXMLElement(num_regular_shipping_element);
   
   TiXmlElement* ship_element = num_regular_shipping_element->NextSiblingElement();
   
   CSC1310::ListDoublyLinkedIterator<Ship>* ship_iter = shipping_lane->iterator();
   while(ship_iter->hasNext())
   {
	   Ship* ship = ship_iter->next();
	   ship->readXML(ship_element, player_images, token_images);
	   ship_element = ship_element->NextSiblingElement();
   }
   delete ship_iter;
}
