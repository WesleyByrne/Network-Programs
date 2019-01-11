#include "AIXML.h"
#include <cstring>

#include <stdexcept>
#include <iostream>

AIXML::AIXML(const char* xml_file_name) : ai_xml_document(xml_file_name)
{
	bool success = ai_xml_document.LoadFile();
	if (!success)
	{
		throw std::runtime_error("Error Parsing XML File");
	}
}

AIXML::~AIXML()
{}

EndeavorBuildingType* AIXML::getBuildingSelectPriorityList()
{
	TiXmlElement* root_element = ai_xml_document.RootElement();
	TiXmlElement* building_select_priority_list_element = root_element->FirstChildElement("building_select_priority_list");
	
	EndeavorBuildingType* building_select_priority_list = new EndeavorBuildingType[15];
	
	TiXmlElement* building_select_priority_element = building_select_priority_list_element->FirstChildElement("building_select_priority");
	int count = 0;
	
	while(building_select_priority_element != NULL)
	{
		const char* building_select_priority_text = building_select_priority_element->GetText();

		if (strcmp(building_select_priority_text, "PARLIAMENT") == 0)
		{
			building_select_priority_list[count] = PARLIAMENT;
		}
		
		else if (strcmp(building_select_priority_text, "EXCHANGE") == 0)
		{
			building_select_priority_list[count] = EXCHANGE;
		}
		
		else if (strcmp(building_select_priority_text, "MUSEUM") == 0)
		{
			building_select_priority_list[count] = MUSEUM;
		}
		
		else if (strcmp(building_select_priority_text, "FORTRESS") == 0)
		{
			building_select_priority_list[count] = FORTRESS;
		}
		
		else if (strcmp(building_select_priority_text, "GUILD_HALL") == 0)
		{
			building_select_priority_list[count] = GUILD_HALL;
		}
		
		else if (strcmp(building_select_priority_text, "UNIVERSITY") == 0)
		{
			building_select_priority_list[count] = UNIVERSITY;
		}
		
		else if (strcmp(building_select_priority_text, "BANK") == 0)
		{
			building_select_priority_list[count] = BANK;
		}
		
		else if (strcmp(building_select_priority_text, "WORKSHOP") == 0)
		{
			building_select_priority_list[count] = WORKSHOP;
		}
		
		else if (strcmp(building_select_priority_text, "SHIPYARD") == 0)
		{
			building_select_priority_list[count] = SHIPYARD;
		}
		
		else if (strcmp(building_select_priority_text, "MARKET") == 0)
		{
			building_select_priority_list[count] = MARKET;
		}
		
		else if (strcmp(building_select_priority_text, "BARRACKS") == 0)
		{
			building_select_priority_list[count] = BARRACKS;
		}
		
		else if (strcmp(building_select_priority_text, "THEATRE") == 0)
		{
			building_select_priority_list[count] = THEATRE;
		}
		
		else if (strcmp(building_select_priority_text, "TRADE_OFFICE") == 0)
		{
			building_select_priority_list[count] = TRADE_OFFICE;
		} 
		
		else if (strcmp(building_select_priority_text, "CARTOGRAPHER") == 0)
		{
			building_select_priority_list[count] = CARTOGRAPHER;
		} 
		
		else
		{
			building_select_priority_list[count] = DOCKS;
		}
		
		count++;
		building_select_priority_element = building_select_priority_element->NextSiblingElement();
	}
	
	return building_select_priority_list;
}

EndeavorBuildingType* AIXML::getBuildingPaymentPriorityList()
{
	TiXmlElement* root_element = ai_xml_document.RootElement();
	TiXmlElement* building_payment_priority_list_element = root_element->FirstChildElement("building_payment_priority_list");
	
	EndeavorBuildingType* building_payment_priority_list = new EndeavorBuildingType[12];
	
	TiXmlElement* building_payment_priority_element = building_payment_priority_list_element->FirstChildElement("building_payment_priority");
	int count = 0;
	
	while(building_payment_priority_element != NULL)
	{
		const char* building_payment_priority_text =building_payment_priority_element->GetText();

		if (strcmp(building_payment_priority_text, "FORTRESS") == 0)
		{
			building_payment_priority_list[count] = FORTRESS;
		}
		
		else if (strcmp(building_payment_priority_text, "GUILD_HALL") == 0)
		{
			building_payment_priority_list[count] = GUILD_HALL;
		}
		
		else if (strcmp(building_payment_priority_text, "DOCKS") == 0)
		{
			building_payment_priority_list[count] = DOCKS;
		}
		
		else if (strcmp(building_payment_priority_text, "COLONIAL_HOUSE") == 0)
		{
			building_payment_priority_list[count] = COLONIAL_HOUSE;
		}
		
		else if (strcmp(building_payment_priority_text, "TRADE_OFFICE") == 0)
		{
			building_payment_priority_list[count] = TRADE_OFFICE;
		}
		
		else if (strcmp(building_payment_priority_text, "CARTOGRAPHER") == 0)
		{
			building_payment_priority_list[count] = CARTOGRAPHER;
		}
		
		else if (strcmp(building_payment_priority_text, "SHIPYARD") == 0)
		{
			building_payment_priority_list[count] = SHIPYARD;
		}
		
		else if (strcmp(building_payment_priority_text, "MARKET") == 0)
		{
			building_payment_priority_list[count] = MARKET;
		}
		
		else if (strcmp(building_payment_priority_text, "BARRACKS") == 0)
		{
			building_payment_priority_list[count] = BARRACKS;
		}
		
		else if (strcmp(building_payment_priority_text, "EXCHANGE") == 0)
		{
			building_payment_priority_list[count] = EXCHANGE;
		}
		
		else if (strcmp(building_payment_priority_text, "MUSEUM") == 0)
		{
			building_payment_priority_list[count] = MUSEUM;
		}
		
		else
		{
			building_payment_priority_list[count] = PARLIAMENT;
		}
		
		count++;
		building_payment_priority_element = building_payment_priority_element->NextSiblingElement();
	}
	

	return building_payment_priority_list;
}

EndeavorTokenType* AIXML::getShipTokenPriorityList()
{
	TiXmlElement* root_element = ai_xml_document.RootElement();
	TiXmlElement* ship_token_priority_list_element = root_element->FirstChildElement("ship_token_priority_list");
	
	EndeavorTokenType* ship_token_priority_list = new EndeavorTokenType[8];
	
	TiXmlElement* ship_token_priority_element = ship_token_priority_list_element->FirstChildElement("ship_token_priority");
	int count = 0;
	
	while(ship_token_priority_element != NULL)
	{
		const char* ship_token_priority_text = ship_token_priority_element->GetText();

		if (strcmp(ship_token_priority_text, "FINANCE") == 0)
		{
			ship_token_priority_list[count] = FINANCE;
		}
		
		else if (strcmp(ship_token_priority_text, "CULTURE") == 0)
		{
			ship_token_priority_list[count] = CULTURE;
		}
		
		else if (strcmp(ship_token_priority_text, "PAYMENT") == 0)
		{
			ship_token_priority_list[count] = PAYMENT;
		}
		
		else if (strcmp(ship_token_priority_text, "INDUSTRY") == 0)
		{
			ship_token_priority_list[count] = INDUSTRY;
		}
		
		else if (strcmp(ship_token_priority_text, "POLITICS") == 0)
		{
			ship_token_priority_list[count] = POLITICS;
		}
		
		else if (strcmp(ship_token_priority_text, "OCCUPY_DRAW") == 0)
		{
			ship_token_priority_list[count] = OCCUPY_DRAW;
		}
		
		else if (strcmp(ship_token_priority_text, "SHIP_DRAW") == 0)
		{
			ship_token_priority_list[count] = SHIP_DRAW;
		}
		
		else
		{
			ship_token_priority_list[count] = ATTACK;
		}
		
		count++;
		ship_token_priority_element = ship_token_priority_element->NextSiblingElement();
	}
	
	return ship_token_priority_list;
}

EndeavorTokenType* AIXML::getCityTokenPriorityList()
{
	TiXmlElement* root_element = ai_xml_document.RootElement();
	TiXmlElement* city_token_priority_list_element = root_element->FirstChildElement("city_token_priority_list");
	
	EndeavorTokenType* city_token_priority_list = new EndeavorTokenType[8];
	
	TiXmlElement* city_token_priority_element = city_token_priority_list_element->FirstChildElement("city_token_priority");
	int count = 0;
	
	while(city_token_priority_element != NULL)
	{
		const char* city_token_priority_text = city_token_priority_element->GetText();

		if (strcmp(city_token_priority_text, "FINANCE") == 0)
		{
			city_token_priority_list[count] = FINANCE;
		}
		
		else if (strcmp(city_token_priority_text, "CULTURE") == 0)
		{
			city_token_priority_list[count] = CULTURE;
		}
		
		else if (strcmp(city_token_priority_text, "PAYMENT") == 0)
		{
			city_token_priority_list[count] = PAYMENT;
		}
		
		else if (strcmp(city_token_priority_text, "INDUSTRY") == 0)
		{
			city_token_priority_list[count] = INDUSTRY;
		}
		
		else if (strcmp(city_token_priority_text, "POLITICS") == 0)
		{
			city_token_priority_list[count] = POLITICS;
		}
		
		else if (strcmp(city_token_priority_text, "OCCUPY_DRAW") == 0)
		{
			city_token_priority_list[count] = OCCUPY_DRAW;
		}
		
		else if (strcmp(city_token_priority_text, "SHIP_DRAW") == 0)
		{
			city_token_priority_list[count] = SHIP_DRAW;
		}
		
		else
		{
			city_token_priority_list[count] = ATTACK;
		}
		
		count++;
		city_token_priority_element = city_token_priority_element->NextSiblingElement();
	}
	
	return city_token_priority_list;
}

EndeavorActionType* AIXML::getActionPriorityList()
{
	TiXmlElement* root_element = ai_xml_document.RootElement();
	TiXmlElement* action_priority_list_element = root_element->FirstChildElement("action_priority_list");
	
	EndeavorActionType* action_priority_list = new EndeavorActionType[5];
	
	TiXmlElement* action_priority_element = action_priority_list_element->FirstChildElement("action_priority");
	int count = 0;
	
	while(action_priority_element != NULL)
	{
		const char* action_priority_text = action_priority_element->GetText();

		if (strcmp(action_priority_text, "OCCUPY") == 0)
		{
			action_priority_list[count] = OCCUPY_ACTION;
		}
		
		else if (strcmp(action_priority_text, "SHIP") == 0)
		{
			action_priority_list[count] = SHIP_ACTION;
		}
		
		else if (strcmp(action_priority_text, "DRAW") == 0)
		{
			action_priority_list[count] = DRAW_ACTION;
		}
		
		else if (strcmp(action_priority_text, "ATTACK") == 0)
		{
			action_priority_list[count] = ATTACK_ACTION;
		}
		
		else
		{
			action_priority_list[count] = PAYMENT_ACTION;
		}
		
		count++;
		action_priority_element = action_priority_element->NextSiblingElement();
	}
	
	return action_priority_list;
}

